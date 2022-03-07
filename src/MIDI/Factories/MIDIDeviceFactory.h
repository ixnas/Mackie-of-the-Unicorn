//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORY_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORY_H

#include "../MIDIDevice.h"

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDevice;
}

namespace MackieOfTheUnicorn::MIDI::Factories
{
	/// Creates a MIDIDevice for a given input and output port number.
	class MIDIDeviceFactory
	{
	  public:
		virtual ~MIDIDeviceFactory() = default;

		/// Returns a new MIDIDevice.
		virtual std::unique_ptr<MIDIDevice> Create(int inputId, int outputId) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORY_H
