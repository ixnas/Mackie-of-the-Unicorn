//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICE_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICE_H

#include <vector>
#include <functional>
#include "MIDIReceiver.h"

namespace MackieOfTheUnicorn::MIDI
{
	/// Provides an interface to communicate with a connected MIDI device.
	class MIDIDevice
	{
	  public:
		virtual ~MIDIDevice() = default;

		/// Sets a callback function for whenever the MIDI device sends a message to the application.
		virtual void RegisterCallback(MIDIReceiver* midiReceiver) = 0;

		/// Sends a MIDI message to the MIDI device.
		virtual void SendMessage(std::vector<unsigned char>& message) = 0;
	};
} // namespace MackieOfTheUnicorn::MIDI

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICE_H
