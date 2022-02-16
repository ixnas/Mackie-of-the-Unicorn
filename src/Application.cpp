//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "Mackie/MackieService.h"
#include "Mixers/LinkedMixer.h"
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

	void Application::Start(const std::vector<std::pair<int, int>>& inputAndOutputIds)
	{
		auto mackieComposite = MackieService->GetMackieComposite(inputAndOutputIds);
		auto mackieMixer = std::make_unique<Mixers::MackieMixer>(mackieComposite, 0);
		std::vector<std::unique_ptr<Mixers::LinkedMixer>> linkedMixers;
		linkedMixers.push_back(std::move(mackieMixer));
		VirtualMixer = std::make_unique<Mixers::VirtualMixerImpl>(linkedMixers);
	}
} // namespace MackieOfTheUnicorn