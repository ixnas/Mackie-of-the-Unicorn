//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#include "MackieCompositeFactoryImpl.h"
#include "../../MIDI/MIDIService.h"
#include "../../MIDI/MIDIDevice.h"
#include "../MackieCompositeImpl.h"
#include "../MackieDevice.h"
#include <memory>
#include <vector>

namespace MackieOfTheUnicorn::Mackie::Factories
{
	MackieCompositeFactoryImpl::MackieCompositeFactoryImpl(MIDI::MIDIService& midiService,
														   Factories::MackieDeviceFactory& mackieDeviceFactory)
	: MIDIService(&midiService), MackieDeviceFactory(&mackieDeviceFactory)
	{
	}

	std::unique_ptr<MackieComposite> MackieCompositeFactoryImpl::Create(
	    const std::vector<std::pair<int, int>>& inputAndOutputIds)
	{
		std::vector<std::unique_ptr<MackieDevice>> mackieDevices;

		for (const auto& inputAndOutputPair : inputAndOutputIds)
		{
			auto midiDevice = MIDIService->GetMIDIDevice(inputAndOutputPair.first, inputAndOutputPair.second);
			auto mackieDevice = MackieDeviceFactory->Create(midiDevice);
			mackieDevices.push_back(std::move(mackieDevice));
		}

		return std::make_unique<MackieCompositeImpl>(mackieDevices);
	}
}