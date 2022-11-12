//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#include <wx/mstream.h>
#include <wx/stdpaths.h>
#include "MainWindow.h"
#include "Identifiers.h"
#include "Icon.cpp"
#include "../Constants.h"
#include "../JSON/JSONSerializer.h"
#include "LicensesWindow.h"

#ifdef WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace MackieOfTheUnicorn::GUI
{
	MainWindow::MainWindow() : wxFrame(NULL, ID_Main_Window, "Mackie of the Unicorn"), application(MackieOfTheUnicorn::BuildApplication())
	{
		url = "";
		input = output = -1;
		started = false;

		wxMemoryInputStream inputStream(APP_ICON, sizeof(APP_ICON));
		wxImage image(inputStream, wxBITMAP_TYPE_PNG);
		image.Rescale(FromDIP(128), FromDIP(128), wxIMAGE_QUALITY_BOX_AVERAGE);
		wxBitmap bitmap(image);

		auto configDir = wxStandardPaths::Get().GetUserConfigDir();
		auto configPathStringBuilder = std::stringstream();
		configPathStringBuilder << configDir << PATH_SEPARATOR << "Mackie-of-the-Unicorn.json";
		configPath = configPathStringBuilder.str();

		Centre();

		auto* menuFile = new wxMenu;
		menuFile->Append(wxID_EXIT);

		auto* menuHelp = new wxMenu;
		menuHelp->Append(wxID_ABOUT);
		menuHelp->Append(ID_Licenses_Menu_Item, "Licenses");

		auto* menuBar = new wxMenuBar;
		menuBar->Append(menuFile, "&File");
		menuBar->Append(menuHelp, "&Help");

		SetMenuBar(menuBar);

		auto inputDevices = application.GetAvailableInputDevices();
		auto outputDevices = application.GetAvailableOutputDevices();

		for (const auto& inputDevice : inputDevices)
		{
			inputChoices.Add(inputDevice.second);
		}

		for (const auto& outputDevice : outputDevices)
		{
			outputChoices.Add(outputDevice.second);
		}

		ReadConfiguration();

		auto* panel = new wxPanel(this);
		auto* vSizer = new wxBoxSizer(wxVERTICAL);
		auto* hSizer = new wxBoxSizer(wxHORIZONTAL);
		auto* configBox = new wxStaticBoxSizer(wxVERTICAL, panel);
		auto* gridSizer = new wxFlexGridSizer(2, FromDIP(12), FromDIP(12));
		urlInput = new wxTextCtrl(panel, ID_Url_Input, url, wxDefaultPosition, FromDIP(wxSize(240, -1)));
		midiInInput = new wxChoice(panel, ID_Midi_Input_Input, wxDefaultPosition, FromDIP(wxSize(240, -1)), inputChoices);
		midiOutInput = new wxChoice(panel, ID_Midi_Output_Input, wxDefaultPosition, FromDIP(wxSize(240, -1)), outputChoices);
		startButton = new wxButton(panel, ID_Connect, wxT("Connect"));
		gridSizer->Add(new wxStaticText(panel, -1, wxT("AVB URL")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
		gridSizer->Add(urlInput, 0, wxALIGN_CENTER_VERTICAL);
		gridSizer->Add(new wxStaticText(panel, -1, wxT("MIDI input")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
		gridSizer->Add(midiInInput, 0, wxALIGN_CENTER_VERTICAL);
		gridSizer->Add(new wxStaticText(panel, -1, wxT("MIDI output")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
		gridSizer->Add(midiOutInput, 0, wxALIGN_CENTER_VERTICAL);
		configBox->Add(gridSizer);
		vSizer->Add(new wxStaticBitmap(panel, -1, bitmap), 0, wxALIGN_CENTER);

		auto version = Constants::GetVersion();
		auto* versionLabel = new wxStaticText(panel, -1, version.data());
		vSizer->Add(versionLabel, 0, wxALIGN_CENTER | wxDOWN, FromDIP(20));
		vSizer->Add(configBox, 1, wxALIGN_CENTER_HORIZONTAL);
		vSizer->Add(startButton, 0, wxALIGN_CENTER | wxUP, FromDIP(24));
		hSizer->Add(vSizer, 1, wxALIGN_CENTER_VERTICAL | wxALL, FromDIP(24));
		panel->SetSizer(hSizer);

		Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
		Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
		Bind(wxEVT_MENU, &MainWindow::OnLicensesClicked, this, ID_Licenses_Menu_Item);
		Bind(wxEVT_BUTTON, &MainWindow::OnConnect, this, ID_Connect);
		Bind(wxEVT_TEXT, &MainWindow::OnUrlChanged, this, ID_Url_Input);
		Bind(wxEVT_CHOICE, &MainWindow::OnInputChanged, this, ID_Midi_Input_Input);
		Bind(wxEVT_CHOICE, &MainWindow::OnOutputChanged, this, ID_Midi_Output_Input);
		Bind(wxEVT_CLOSE_WINDOW, &MainWindow::WriteConfiguration, this, ID_Main_Window);

		if (!inputChoices.empty())
		{
			if (input == -1)
			{
				input = 0;
			}
			midiInInput->SetSelection(input);
		}

		if (!outputChoices.empty())
		{
			if (output == -1)
			{
				output = 0;
			}
			midiOutInput->SetSelection(output);
		}

		CheckEnabledElements();

		Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnExit));
		hSizer->Fit(this);
		SetSizeHints(GetSize(), GetSize());

	}
	void MainWindow::OnExit(wxCommandEvent& event)
	{
		Close(true);
	}
	void MainWindow::OnAbout(wxCommandEvent& event)
	{
		std::stringstream msg;
		msg << "Version " << Constants::GetVersion().data() << std::endl << "Copyright © " << Constants::GetYear().data() << " Sjoerd Scheffer";
		auto msgString = msg.str();
		wxMessageBox(msgString, "Mackie of the Unicorn", wxOK | wxICON_INFORMATION);
	}
	void MainWindow::OnConnect(wxCommandEvent& event)
	{
		if (!startButton->IsEnabled())
		{
			return;
		}

		if (started)
		{
			application = MackieOfTheUnicorn::BuildApplication();
			started = false;
			CheckEnabledElements();
			return;
		}

		std::vector<std::pair<int, int>> inputsAndOutputs = {{input, output}};
		application.Start(inputsAndOutputs, url);
		started = true;
		CheckEnabledElements();
	}

	void MainWindow::OnUrlChanged(wxCommandEvent& event)
	{
		url = event.GetString();
		CheckEnabledElements();
	}

	void MainWindow::OnInputChanged(wxCommandEvent& event)
	{
		input = event.GetInt();
		CheckEnabledElements();
	}

	void MainWindow::OnOutputChanged(wxCommandEvent& event)
	{
		output = event.GetInt();
		CheckEnabledElements();
	}

	void MainWindow::CheckEnabledElements()
	{
		if (started) {
			startButton->Enable(true);
			midiInInput->Enable(false);
			midiOutInput->Enable(false);
			urlInput->Enable(false);
			startButton->SetLabel(wxT("Disconnect"));
			return;
		}

		if (input == -1 || output == -1 || url.empty())
		{
			startButton->Enable(false);
			return;
		}

		startButton->Enable(true);
		midiInInput->Enable(true);
		midiOutInput->Enable(true);
		urlInput->Enable(true);
		startButton->SetLabel(wxT("Connect"));
	}

	void MainWindow::ReadConfiguration()
	{
		std::ifstream stream(configPath);

		if (!stream.good())
		{
			return;
		}

		std::string configString((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
		using namespace MackieOfTheUnicorn::JSON;
		auto jsonDocument = JSONSerializer::Parse(configString);
		for (const auto& pair : jsonDocument)
		{
			auto key = pair.first;
			auto value = pair.second;
			if (key == "url")
			{
				url = value.String.value();
			}
			if (key == "midiInputNumber" && inputChoices.size() > value.Integer.value() && value.Integer.value() != -1)
			{
				input = value.Integer.value();
			}
			if (key == "midiOutputNumber" && outputChoices.size() > value.Integer.value() && value.Integer.value() != -1)
			{
				output = value.Integer.value();
			}
		}
	}

	void MainWindow::WriteConfiguration(wxCloseEvent& event)
	{
		std::ofstream stream(configPath, std::ios::trunc);

		if (!stream.good())
		{
			return;
		}

		using namespace MackieOfTheUnicorn::JSON;
		std::vector<std::pair<std::string, JSONValue>> configuration;

		std::string versionKey = "configVersion";
		JSONValue versionValue;
		versionValue.Integer = 1;

		configuration.emplace_back(versionKey, versionValue);

		std::string urlKey = "url";
		JSONValue urlValue;
		urlValue.String = url;

		configuration.emplace_back(urlKey, urlValue);

		std::string inputKey = "midiInputNumber";
		JSONValue inputValue;
		inputValue.Integer = input;

		configuration.emplace_back(inputKey, inputValue);

		std::string outputKey = "midiOutputNumber";
		JSONValue outputValue;
		outputValue.Integer = output;

		configuration.emplace_back(outputKey, outputValue);

		auto serialized = JSONSerializer::Serialize(configuration);

		stream << serialized;

		stream.close();
		event.Skip();
	}

	void MainWindow::OnLicensesClicked(wxCommandEvent& event)
	{
		auto* licenseFrame = new LicensesWindow();
		licenseFrame->Show(true);
	}
}
