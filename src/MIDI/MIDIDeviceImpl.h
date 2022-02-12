//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIDEVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_MIDIDEVICEIMPL_H

#include "MIDIDevice.h"
#include "../LibraryAbstractions/RtMidi/RtMidiInAbstraction.h"
#include "../LibraryAbstractions/RtMidi/RtMidiOutAbstraction.h"
#include <memory>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{
	class RtMidiAbstractionFactory;
}

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDeviceImpl : public MIDIDevice
	{
		std::unique_ptr<LibraryAbstractions::RtMidi::RtMidiInAbstraction> RtMidiIn;
		std::unique_ptr<LibraryAbstractions::RtMidi::RtMidiOutAbstraction> RtMidiOut;

	  public:
		explicit MIDIDeviceImpl(LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiFactory);
		void RegisterCallback(std::function<void(std::vector<unsigned char>)> callback) override;
		void SendMessage(std::vector<unsigned char> message) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEIMPL_H
