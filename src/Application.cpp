//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "Mackie/MackieService.h"
#include "Mixers/VirtualMixerBuilder.h"
#include "Mixers/VirtualMixerImpl.h"

namespace MackieOfTheUnicorn
{
	Application::Application(Mackie::MackieService& mackieService) : MackieService(&mackieService)
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

	void Application::Start(std::vector<std::pair<int, int>>& inputAndOutputIds)
	{
		auto virtualMixerBuilder = std::make_unique<Mixers::VirtualMixerBuilder>(*MackieService);
		VirtualMixer = virtualMixerBuilder->AddMackieMixer(inputAndOutputIds)->Build();
	}
} // namespace MackieOfTheUnicorn