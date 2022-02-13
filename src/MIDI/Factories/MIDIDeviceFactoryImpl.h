//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORYIMPL_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORYIMPL_H

#include "MIDIDeviceFactory.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{
	class RtMidiAbstractionFactory;
}

namespace MackieOfTheUnicorn::MIDI::Factories
{
	class MIDIDeviceFactoryImpl : public MIDIDeviceFactory
	{
		LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory* RtMidiAbstractionFactory;

	  public:
		explicit MIDIDeviceFactoryImpl(LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiAbstractionFactory);
		std::unique_ptr<MIDIDevice> Create(int inputId, int outputId) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEFACTORYIMPL_H
