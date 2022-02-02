//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORY_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORY_H

#include <memory>

class MackieDevice;
class MIDIDevice;

class MackieDeviceFactory
{
  public:
	virtual ~MackieDeviceFactory() = default;
	virtual std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDIDevice> midiDevice) = 0;
};

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORY_H
