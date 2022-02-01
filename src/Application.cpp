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

	if (devices.empty())
	{
		return GetNoAvailableDevices();
	}

	return GetAvailableDevicesList(devices);
}

std::string Application::GetAvailableDevicesList(const std::map<int, std::string>& devices)
{
	std::ostringstream output;
	output << "Available devices:" << std::endl;
	for (const auto& device : devices)
	{
		output << device.first << ": " << device.second << std::endl;
	}
	return output.str();
}

std::string Application::GetNoAvailableDevices()
{
	std::ostringstream output;
	output << "No available devices." << std::endl;
	return output.str();
}
