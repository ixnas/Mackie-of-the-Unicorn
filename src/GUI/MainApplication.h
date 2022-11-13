//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MAINAPPLICATION_H
#define MACKIE_OF_THE_UNICORN_MAINAPPLICATION_H

#include <wx/wxprec.h> // This header is normally included from wx/wx.h
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace MackieOfTheUnicorn::GUI
{
	/// Main GUI application class.
	class MainApplication : public wxApp
	{
	  public:
		bool OnInit() override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MAINAPPLICATION_H
