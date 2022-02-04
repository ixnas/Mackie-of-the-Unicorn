//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDISERVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MIDISERVICEFAKE_H

#include "../src/MIDIService.h"
#include "MIDIDeviceFake.h"

class MIDIServiceFake : public MIDIService
{
  public:
	std::map<int, std::string> GetInputDevices() override
	{
		return {{0, "in1"}, {1, "in2"}};
	}

	std::map<int, std::string> GetOutputDevices() override
	{
		return {{0, "out1"}, {1, "out2"}};
	}

	std::unique_ptr<MIDIDevice> GetMIDIDevice(int inputId, int outputId) override
	{
		return std::make_unique<MIDIDeviceFake>();
	}
};

#endif // MACKIE_OF_THE_UNICORN_MIDISERVICEFAKE_H
