//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "MackieService.h"
#include <iostream>

Application::Application(::MackieService& mackieService) : MackieService(&mackieService)
{
}

void Application::Start()
{
	std::cout << MackieService->GetDevices().size() << std::endl;
}
