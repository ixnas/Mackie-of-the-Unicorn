//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LICENSESWINDOW_H
#define MACKIE_OF_THE_UNICORN_LICENSESWINDOW_H

#include <wx/wxprec.h> // This header is normally included from wx/wx.h
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace MackieOfTheUnicorn::GUI
{
	/// A window with a read-only text control showing the project's associated licenses.
	class LicensesWindow : public wxFrame
	{
	  public:
		LicensesWindow();
	};
}

#endif // MACKIE_OF_THE_UNICORN_LICENSESWINDOW_H
