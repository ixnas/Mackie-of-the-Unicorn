//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#include "LicensesWindow.h"
#include "Identifiers.h"
#include "../Constants.h"

namespace MackieOfTheUnicorn::GUI
{
	LicensesWindow::LicensesWindow() : wxFrame(NULL, ID_License_Window, "Licenses")
	{
		auto size = wxSize(FromDIP(500), FromDIP(500));
		this->SetSize(size);
		this->SetSizeHints(size);
		auto* panel = new wxPanel(this);
		auto* sizer = new wxBoxSizer(wxVERTICAL);
		auto licenses = Constants::GetLicenses();
		auto* textCtrl = new wxTextCtrl(panel, -1, licenses.data(), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
		sizer->Add(textCtrl, 1, wxEXPAND | wxALL);
		panel->SetSizer(sizer);
	}
}