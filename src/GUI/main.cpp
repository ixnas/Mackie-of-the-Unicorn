//
// Created by Sjoerd Scheffer on 10/02/2022.
//

#include "wx/wxprec.h" // This header is normally included from wx/wx.h
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../git_version.h"
#include "../Application.h"

class MyApp : public wxApp
{
  public:
	bool OnInit() override;
};
class MyFrame : public wxFrame
{
  public:
	MyFrame();

  private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
enum
{
	ID_Hello = 1,
};
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame();
	frame->Show(true);
	return true;
}
MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Mackie of the Unicorn")
{
	this->SetSize(this->FromDIP(wxSize(380, 180)));
	this->SetMinSize(this->FromDIP(wxSize(380, 180)));
	this->SetMaxSize(this->FromDIP(wxSize(380, 180)));

	Centre();

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	auto application = MackieOfTheUnicorn::BuildApplication();

	auto inputDevices = application.GetAvailableInputDevices();
	auto outputDevices = application.GetAvailableOutputDevices();

	auto inputChoices = wxArrayString();
	auto outputChoices = wxArrayString();

	for (const auto& inputDevice : inputDevices)
	{
		inputChoices.Add(inputDevice.second);
	}

	for (const auto& outputDevice : outputDevices)
	{
		outputChoices.Add(outputDevice.second);
	}

	wxPanel* panel = new wxPanel(this);
	wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hSizer = new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 12, 12);
	wxTextCtrl* urlInput = new wxTextCtrl(panel, -1, wxEmptyString, wxDefaultPosition, wxSize(200, -1));
	wxChoice* midiInInput = new wxChoice(panel, -1, wxDefaultPosition, wxSize(200, -1), inputChoices);
	wxChoice* midiOutInput = new wxChoice(panel, -1, wxDefaultPosition, wxSize(200, -1), outputChoices);
	wxButton* startButton = new wxButton(panel, -1, wxT("Connect"));
	gridSizer->Add(new wxStaticText(panel, -1, wxT("URL")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(urlInput, 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(new wxStaticText(panel, -1, wxT("MIDI input")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(midiInInput, 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(new wxStaticText(panel, -1, wxT("MIDI output")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(midiOutInput, 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(new wxStaticText(panel, -1, wxT("")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(startButton, 0);
	vSizer->Add(gridSizer, 1, wxALIGN_CENTER_HORIZONTAL);
	hSizer->Add(vSizer, 1, wxALIGN_CENTER_VERTICAL);
	panel->SetSizer(hSizer);

	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnExit));
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