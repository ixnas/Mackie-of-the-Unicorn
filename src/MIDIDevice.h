//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICE_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICE_H

#include <vector>

class MIDIDevice
{
  public:
	virtual ~MIDIDevice() = default;
	virtual void RegisterCallback(std::function<void(std::vector<unsigned char>)> callback) = 0;
	virtual void SendMessage(std::vector<unsigned char> message) = 0;
};

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICE_H
