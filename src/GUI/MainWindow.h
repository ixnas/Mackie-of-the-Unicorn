//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MAINWINDOW_H
#define MACKIE_OF_THE_UNICORN_MAINWINDOW_H

#include <wx/wxprec.h> // This header is normally included from wx/wx.h
#include "../Application.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace MackieOfTheUnicorn::GUI
{
	class MainWindow : public wxFrame
	{
	  public:
		MainWindow();

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

}

#endif // MACKIE_OF_THE_UNICORN_MAINWINDOW_H
