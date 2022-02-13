//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORYFAKE_H

#include "../../../../src/MIDI/Factories/MIDIDeviceFactory.h"
#include "../MIDIDeviceFake.h"

namespace MackieOfTheUnicorn::MIDI::Factories
{
	class MIDIDeviceFactoryFake : public MIDIDeviceFactory
	{
	  public:
		std::unique_ptr<MIDIDevice> Create(int inputId, int outputId) override
		{
			return std::make_unique<MIDIDeviceFake>(inputId, outputId);
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORYFAKE_H
