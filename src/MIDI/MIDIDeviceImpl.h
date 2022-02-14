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

		static void CallbackProxy(double deltaTime, std::vector<unsigned char>* message, void* userData);

	  public:
		explicit MIDIDeviceImpl(LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiFactory,
		                        int inputId, int outputId);
		void RegisterCallback(MIDIReceiver *midiReceiver) override;
		void SendMessage(std::vector<unsigned char>& message) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDIDEVICEIMPL_H
