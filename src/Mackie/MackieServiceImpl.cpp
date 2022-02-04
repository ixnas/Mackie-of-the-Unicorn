//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "MackieServiceImpl.h"
#include "../MIDI/MIDIDevice.h"
#include "../MIDI/MIDIService.h"
#include "MackieComposite.h"
#include "Factories/MackieCompositeFactory.h"
#include "MackieDevice.h"
#include "Factories/MackieDeviceFactory.h"
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	MackieServiceImpl::MackieServiceImpl(Factories::MackieCompositeFactory& mackieCompositeFactory,
	                                     Factories::MackieDeviceFactory& mackieDeviceFactory, MIDI::MIDIService& midiService)
	    : MackieCompositeFactory(&mackieCompositeFactory), MackieDeviceFactory(&mackieDeviceFactory),
	      MIDIService(&midiService)
	{
	}

	std::map<int, std::string> MackieServiceImpl::GetInputDevices()
	{
		return MIDIService->GetInputDevices();
	}

	std::map<int, std::string> MackieServiceImpl::GetOutputDevices()
	{
		return MIDIService->GetOutputDevices();
	}

	std::unique_ptr<MackieComposite> MackieServiceImpl::GetMackieComposite(
	    const std::vector<std::pair<int, int>>& inAndOutputIds)
	{
		auto mackieDevices = std::vector<std::unique_ptr<MackieDevice>>();
		for (const auto& deviceId : inAndOutputIds)
		{
			auto midiDevice = MIDIService->GetMIDIDevice(deviceId.first, deviceId.second);
			auto mackieDevice = MackieDeviceFactory->Create(std::move(midiDevice));
			mackieDevices.push_back(std::move(mackieDevice));
		}
		return MackieCompositeFactory->Create(std::move(mackieDevices));
	}
}
