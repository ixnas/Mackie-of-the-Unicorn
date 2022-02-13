//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDISERVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_MIDISERVICEIMPL_H

#include "MIDIService.h"
#include "../LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactory.h"
#include "../LibraryAbstractions/RtMidi/RtMidiOutAbstraction.h"
#include "../LibraryAbstractions/RtMidi/RtMidiInAbstraction.h"
#include <memory>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{
	class RtMidiAbstractionFactory;
}

namespace MackieOfTheUnicorn::MIDI::Factories
{
	class MIDIDeviceFactory;
}

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDevice;

	class MIDIServiceImpl : public MIDIService
	{
		Factories::MIDIDeviceFactory* MIDIDeviceFactory;
		std::unique_ptr<LibraryAbstractions::RtMidi::RtMidiInAbstraction> RtMidiIn;
		std::unique_ptr<LibraryAbstractions::RtMidi::RtMidiOutAbstraction> RtMidiOut;

	  public:
		explicit MIDIServiceImpl(
		    LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiAbstractionFactory,
		    Factories::MIDIDeviceFactory& midiDeviceFactory);
		std::map<int, std::string> GetInputDevices() override;
		std::map<int, std::string> GetOutputDevices() override;
		std::unique_ptr<MIDIDevice> GetMIDIDevice(int inputId, int outputId) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDISERVICEIMPL_H
