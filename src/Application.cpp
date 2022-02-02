//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "MackieService.h"

Application::Application(::MackieService& mackieService) : MackieService(&mackieService)
{
}

std::map<int, std::string> Application::GetAvailableInputDevices() const
{
	return MackieService->GetInputDevices();
}

std::map<int, std::string> Application::GetAvailableOutputDevices() const
{
	return MackieService->GetOutputDevices();
}
