//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#include "MainApplication.h"
#include "MainWindow.h"

namespace MackieOfTheUnicorn::GUI
{
	bool MainApplication::OnInit()
	{
		SetAppName("Mackie of the Unicorn");
		wxInitAllImageHandlers();
		auto* frame = new MainWindow();
		frame->Show(true);
		return true;
	}
}
