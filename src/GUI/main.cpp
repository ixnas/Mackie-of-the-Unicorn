//
// Created by Sjoerd Scheffer on 10/02/2022.
//

#include "wx/wxprec.h" // This header is normally included from wx/wx.h
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/stdpaths.h>
#include <wx/imagpng.h>
#include <wx/mstream.h>

#include "../git_version.h"
#include "../Application.h"
#include "../JSON/JSONSerializer.h"
#include "../../assets/icon.c"

class MyApp : public wxApp
{
  public:
	bool OnInit() override;
};
class LicenseFrame : public wxFrame
{
  public:
	LicenseFrame();
};
class MyFrame : public wxFrame
{
  public:
	MyFrame();

  private:
	wxButton* startButton;
	wxTextCtrl* urlInput;
	wxArrayString inputChoices;
	wxArrayString outputChoices;
	wxChoice* midiInInput;
	wxChoice* midiOutInput;
	MackieOfTheUnicorn::Application application;
	std::string url;
	std::string configPath;
	int input, output;
	bool started;
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnConnect(wxCommandEvent& event);
	void OnUrlChanged(wxCommandEvent& event);
	void OnInputChanged(wxCommandEvent& event);
	void OnOutputChanged(wxCommandEvent& event);
	void CheckEnabledElements();
	void ReadConfiguration();
	void WriteConfiguration(wxCloseEvent& event);
	void OnLicensesClicked(wxCommandEvent& event);
};

enum
{
	ID_Connect = 1,
	ID_Url_Input = 2,
	ID_Midi_Input_Input = 3,
	ID_Midi_Output_Input = 4,
	ID_Main_Window = 5,
	ID_License_Window = 6,
	ID_Licenses_Menu_Item = 7
};
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	SetAppName("Mackie of the Unicorn");
	wxInitAllImageHandlers();
	MyFrame* frame = new MyFrame();
	frame->Show(true);
	return true;
}
MyFrame::MyFrame() : wxFrame(NULL, ID_Main_Window, "Mackie of the Unicorn"), application(MackieOfTheUnicorn::BuildApplication())
{
	url = "";
	input = output = -1;
	started = false;

#ifdef WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

	wxMemoryInputStream inputStream(_acicon, sizeof(_acicon));
	wxImage image(inputStream, wxBITMAP_TYPE_PNG);
	image.Rescale(this->FromDIP(128), this->FromDIP(128), wxIMAGE_QUALITY_BOX_AVERAGE);
	wxBitmap bitmap(image);

	auto configDir = wxStandardPaths::Get().GetUserConfigDir();
	auto configPathStringBuilder = std::stringstream();
	configPathStringBuilder << configDir << PATH_SEPARATOR << "Mackie-of-the-Unicorn.json";
	configPath = configPathStringBuilder.str();

	Centre();

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	menuHelp->Append(ID_Licenses_Menu_Item, "Licenses");

	wxMenuBar* menuBar = new wxMenuBar;
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

	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer* configBox = new wxStaticBoxSizer(wxVERTICAL, panel);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, this->FromDIP(12), this->FromDIP(12));
	urlInput = new wxTextCtrl(panel, ID_Url_Input, url, wxDefaultPosition, this->FromDIP(wxSize(240, -1)));
	midiInInput = new wxChoice(panel, ID_Midi_Input_Input, wxDefaultPosition, this->FromDIP(wxSize(240, -1)), inputChoices);
	midiOutInput = new wxChoice(panel, ID_Midi_Output_Input, wxDefaultPosition, this->FromDIP(wxSize(240, -1)), outputChoices);
	startButton = new wxButton(panel, ID_Connect, wxT("Connect"));
	gridSizer->Add(new wxStaticText(panel, -1, wxT("URL")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(urlInput, 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(new wxStaticText(panel, -1, wxT("MIDI input")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(midiInInput, 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(new wxStaticText(panel, -1, wxT("MIDI output")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(midiOutInput, 0, wxALIGN_CENTER_VERTICAL);
	configBox->Add(gridSizer);
	vSizer->Add(new wxStaticBitmap(panel, -1, bitmap), 0, wxALIGN_CENTER);

	wxStaticText* versionLabel = new wxStaticText(panel, -1, MackieOfTheUnicorn::VERSION);
	vSizer->Add(versionLabel, 0, wxALIGN_CENTER | wxDOWN, this->FromDIP(20));
	vSizer->Add(configBox, 1, wxALIGN_CENTER_HORIZONTAL);
	vSizer->Add(startButton, 0, wxALIGN_CENTER | wxUP, this->FromDIP(24));
	hSizer->Add(vSizer, 1, wxALIGN_CENTER_VERTICAL | wxALL, this->FromDIP(24));
	panel->SetSizer(hSizer);

	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MyFrame::OnLicensesClicked, this, ID_Licenses_Menu_Item);
	Bind(wxEVT_BUTTON, &MyFrame::OnConnect, this, ID_Connect);
	Bind(wxEVT_TEXT, &MyFrame::OnUrlChanged, this, ID_Url_Input);
	Bind(wxEVT_CHOICE, &MyFrame::OnInputChanged, this, ID_Midi_Input_Input);
	Bind(wxEVT_CHOICE, &MyFrame::OnOutputChanged, this, ID_Midi_Output_Input);
	Bind(wxEVT_CLOSE_WINDOW, &MyFrame::WriteConfiguration, this, ID_Main_Window);

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

	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnExit));
	hSizer->Fit(this);
	this->SetSizeHints(this->GetSize(), this->GetSize());

}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	std::stringstream msg;
	msg << "Version " << MackieOfTheUnicorn::VERSION << std::endl << "Copyright © " << MackieOfTheUnicorn::YEAR << " Sjoerd Scheffer";
	auto msgString = msg.str();
	wxMessageBox(msgString, "Mackie of the Unicorn", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnConnect(wxCommandEvent& event)
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

void MyFrame::OnUrlChanged(wxCommandEvent& event)
{
	url = event.GetString();
	CheckEnabledElements();
}

void MyFrame::OnInputChanged(wxCommandEvent& event)
{
	input = event.GetInt();
	CheckEnabledElements();
}

void MyFrame::OnOutputChanged(wxCommandEvent& event)
{
	output = event.GetInt();
	CheckEnabledElements();
}

void MyFrame::CheckEnabledElements()
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

void MyFrame::ReadConfiguration()
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

void MyFrame::WriteConfiguration(wxCloseEvent& event)
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

void MyFrame::OnLicensesClicked(wxCommandEvent& event)
{
	LicenseFrame* licenseFrame = new LicenseFrame();
	licenseFrame->Show(true);
}

LicenseFrame::LicenseFrame() : wxFrame(NULL, ID_License_Window, "Licenses")
{
	auto size = wxSize(FromDIP(500), FromDIP(500));
	this->SetSize(size);
	this->SetSizeHints(size);
	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxTextCtrl* textCtrl = new wxTextCtrl(panel, -1, MackieOfTheUnicorn::LICENSES, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	sizer->Add(textCtrl, 1, wxEXPAND | wxALL);
	panel->SetSizer(sizer);
}