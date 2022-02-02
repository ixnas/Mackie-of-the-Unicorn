//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "MackieServiceImpl.h"
#include "MIDIDevice.h"
#include "MIDIService.h"
#include "MackieComposite.h"
#include "MackieCompositeFactory.h"
#include "MackieDevice.h"
#include "MackieDeviceFactory.h"
#include <vector>

MackieServiceImpl::MackieServiceImpl(::MackieCompositeFactory& mackieCompositeFactory,
                                     ::MackieDeviceFactory& mackieDeviceFactory, ::MIDIService& midiService)
    : MackieCompositeFactory(&mackieCompositeFactory), MackieDeviceFactory(&mackieDeviceFactory),
      MIDIService(&midiService)
{
}

std::map<int, std::string> MackieServiceImpl::GetDevices()
{
	return MIDIService->GetDevices();
}

std::unique_ptr<MackieComposite> MackieServiceImpl::GetMackieComposite(std::vector<int> deviceIds)
{
	auto mackieDevices = std::vector<std::unique_ptr<MackieDevice>>();
	for (const auto& deviceId : deviceIds)
	{
		auto midiDevice = MIDIService->GetMIDIDevice(deviceId);
		auto mackieDevice = MackieDeviceFactory->Create(std::move(midiDevice));
		mackieDevices.push_back(std::move(mackieDevice));
	}
	return MackieCompositeFactory->Create(std::move(mackieDevices));
}
