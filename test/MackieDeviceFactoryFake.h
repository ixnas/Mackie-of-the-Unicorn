//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYFAKE_H

#include "../src/MackieDeviceFactory.h"
#include "MackieDeviceFake.h"

class MackieDeviceFactoryFake : public MackieDeviceFactory
{
  public:
	std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDIDevice> midiDevice) override
	{
		return std::make_unique<MackieDeviceFake>();
	}
};

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORYFAKE_H
