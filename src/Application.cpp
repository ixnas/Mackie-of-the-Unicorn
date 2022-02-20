//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "Mackie/MackieService.h"
#include "Mixers/VirtualMixerBuilder.h"
#include "Mixers/VirtualMixerImpl.h"

namespace MackieOfTheUnicorn
{
	Application::Application(Mackie::MackieService& mackieService, Mixers::VirtualMixerBuilder& virtualMixerBuilder) : MackieService(&mackieService), VirtualMixerBuilder(&virtualMixerBuilder)
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
		VirtualMixer = VirtualMixerBuilder->AddMackieMixer(inputAndOutputIds)->AddMOTUMixer("169.254.133.172")->Build();
	}
} // namespace MackieOfTheUnicorn