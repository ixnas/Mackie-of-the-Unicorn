//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDISERVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MIDISERVICEFAKE_H

#include "../../../src/MIDI/MIDIService.h"
#include "MIDIDeviceFake.h"

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIServiceFake : public MIDIService
	{
	  public:
		std::map<int, std::string> InputDevices;
		std::map<int, std::string> OutputDevices;

		std::map<int, std::string> GetInputDevices() override
		{
			return InputDevices;
		}

		std::map<int, std::string> GetOutputDevices() override
		{
			return OutputDevices;
		}

		std::unique_ptr<MIDIDevice> GetMIDIDevice(int inputId, int outputId) override
		{
			return std::make_unique<MIDIDeviceFake>();
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDISERVICEFAKE_H
