//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "MackieService.h"
#include <iostream>
#include <sstream>

Application::Application(::MackieService& mackieService) : MackieService(&mackieService)
{
}

std::string Application::GetAvailableDevices() const
{
	const auto devices = MackieService->GetDevices();
	std::ostringstream output;

	if (devices.empty())
	{
		output << "No available devices." << std::endl;
		return output.str();
	}

	output << "Available devices:" << std::endl;
	for (const auto& device : devices)
	{
		output << device.first << ": " << device.second << std::endl;
	}
	return output.str();
}
