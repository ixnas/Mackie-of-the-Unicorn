//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICEFAKE_H

#include "../../../src/MIDI/MIDIDevice.h"

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDeviceFake : public MIDIDevice
	{
	  public:
		void RegisterCallback(MIDIReceiver *midiReceiver) override
		{
		}

		void SendMessage(std::vector<unsigned char> message) override
		{
		}
	};
} // namespace MackieOfTheUnicorn::MIDI

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEFAKE_H
