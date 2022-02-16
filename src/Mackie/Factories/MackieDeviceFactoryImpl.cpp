//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#include "MackieDeviceFactoryImpl.h"
#include "../MackieDeviceImpl.h"
#include <memory>

namespace MackieOfTheUnicorn::Mackie::Factories
{
	std::unique_ptr<MackieDevice> MackieDeviceFactoryImpl::Create(std::unique_ptr<MIDI::MIDIDevice>& midiDevice)
	{
		return std::make_unique<MackieDeviceImpl>(midiDevice);
	}
}
