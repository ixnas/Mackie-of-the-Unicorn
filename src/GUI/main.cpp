//
// Created by Sjoerd Scheffer on 10/02/2022.
//

#include "wx/wxprec.h" // This header is normally included from wx/wx.h
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "../git_version.h"

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
	void OnHello(wxCommandEvent& event);
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
	this->SetSize(this->FromDIP(wxSize(400, 300)));
	this->SetMinSize(this->FromDIP(wxSize(400, 300)));
	this->SetMaxSize(this->FromDIP(wxSize(400, 300)));

	Centre();

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();

	wxPanel* panel = new wxPanel(this, -1);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxPanel* ipPanel = new wxPanel(panel, wxID_ANY);
	wxBoxSizer* middleSizer = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* ipAddressLabel = new wxPanel(ipPanel, wxID_ANY);
	new wxStaticText(ipAddressLabel, wxID_ANY, "AVB IP address:");

	wxPanel* ipAddressField = new wxPanel(ipPanel, wxID_ANY);
	new wxTextCtrl(ipAddressField, wxID_ANY);

	middleSizer->Add(ipAddressLabel, 1, wxALIGN_CENTER);
	middleSizer->Add(ipAddressField, 1, wxALIGN_CENTER);
	ipPanel->SetSizer(middleSizer);

	wxPanel* midiInPanel = new wxPanel(panel, wxID_ANY);
	wxBoxSizer* midiInPanelSizer = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* midiInLabel = new wxPanel(midiInPanel, wxID_ANY);
	new wxStaticText(midiInLabel, wxID_ANY, "MIDI input device:");

	wxPanel* midiInField = new wxPanel(midiInPanel, wxID_ANY);
	wxChoice* midiInFieldChoice = new wxChoice(midiInField, wxID_ANY);
	wxString inChoices[] {"Device 0", "Device 1"};
	midiInFieldChoice->Set(2, inChoices);

	midiInPanelSizer->Add(midiInLabel, 1, wxALIGN_CENTER);
	midiInPanelSizer->Add(midiInField, 1, wxALIGN_CENTER);
	midiInPanel->SetSizer(midiInPanelSizer);

	wxPanel* midiOutPanel = new wxPanel(panel, wxID_ANY);
	wxBoxSizer* midiOutPanelSizer = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* midiOutLabel = new wxPanel(midiOutPanel, wxID_ANY);
	new wxStaticText(midiOutLabel, wxID_ANY, "MIDI output device:");

	wxPanel* midiOutField = new wxPanel(midiOutPanel, wxID_ANY);
	wxChoice* midiOutFieldChoice = new wxChoice(midiOutField, wxID_ANY);
	wxString outChoices[] {"Device 0", "Device 1"};
	midiOutFieldChoice->Set(2, outChoices);

	midiOutPanelSizer->Add(midiOutLabel, 1, wxALIGN_CENTER);
	midiOutPanelSizer->Add(midiOutField, 1, wxALIGN_CENTER);
	midiOutPanel->SetSizer(midiOutPanelSizer);

	wxPanel* bottomPanel = new wxPanel(panel, wxID_ANY);
	new wxButton(bottomPanel, wxID_EXIT, _T("Connect"));

	sizer->Add(ipPanel, 1, wxALIGN_CENTER);
	sizer->Add(midiInPanel, 1, wxALIGN_CENTER);
	sizer->Add(midiOutPanel, 1, wxALIGN_CENTER);
	sizer->Add(bottomPanel, 1, wxALIGN_CENTER);
	panel->SetSizer(sizer);

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