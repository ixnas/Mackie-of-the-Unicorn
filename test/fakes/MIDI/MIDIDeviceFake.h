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
		int InputId;
		int OutputId;
		std::vector<std::vector<unsigned char>> SendMessageMessages;
		MIDIReceiver* MIDIReceiver;

		explicit MIDIDeviceFake(int inputId, int outputId) : InputId(inputId), OutputId(outputId)
		{
		}

		void RegisterCallback(MIDI::MIDIReceiver *midiReceiver) override
		{
			MIDIReceiver = midiReceiver;
		}

		void SendMessage(std::vector<unsigned char>& message) override
		{
			SendMessageMessages.push_back(message);
		}

		void FakeMessage(std::vector<unsigned char> message) const
		{
			MIDIReceiver->MIDICallback(message);
		}
	};
} // namespace MackieOfTheUnicorn::MIDI

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEFAKE_H
