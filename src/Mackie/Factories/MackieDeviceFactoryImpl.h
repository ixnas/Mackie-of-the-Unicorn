//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYIMPL_H

#include "MackieDeviceFactory.h"
#include "../../MIDI/MIDIDevice.h"
#include "../MackieDevice.h"

namespace MackieOfTheUnicorn::Mackie::Factories
{
	class MackieDeviceFactoryImpl : public MackieDeviceFactory
	{
	  public:
		std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDI::MIDIDevice>& midiDevice) override;
	};
} // namespace MackieOfTheUnicorn::Mackie::Factories

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYIMPL_H
