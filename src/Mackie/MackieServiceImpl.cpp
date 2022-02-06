//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "MackieServiceImpl.h"
#include "../MIDI/MIDIDevice.h"
#include "../MIDI/MIDIService.h"
#include "Factories/MackieCompositeFactory.h"
#include "Factories/MackieDeviceFactory.h"
#include "MackieComposite.h"
#include "MackieDevice.h"
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	MackieServiceImpl::MackieServiceImpl(Factories::MackieCompositeFactory& mackieCompositeFactory,
	                                     MIDI::MIDIService& midiService)
	    : MackieCompositeFactory(&mackieCompositeFactory), MIDIService(&midiService)
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
	    const std::vector<std::pair<int, int>>& inputAndOutputIds)
	{
		return MackieCompositeFactory->Create(inputAndOutputIds);
	}
} // namespace MackieOfTheUnicorn::Mackie
