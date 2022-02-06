//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYFAKE_H

#include "../../../../src/Mackie/Factories/MackieDeviceFactory.h"
#include "../MackieDeviceFake.h"

namespace MackieOfTheUnicorn::Mackie::Factories
{
	class MackieDeviceFactoryFake : public MackieDeviceFactory
	{
	  public:
		std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDI::MIDIDevice> midiDevice) override
		{
			return std::make_unique<MackieDeviceFake>();
		}
	};
} // namespace MackieOfTheUnicorn::Mackie::Factories

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYFAKE_H
