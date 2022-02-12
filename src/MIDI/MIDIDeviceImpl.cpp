//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "MIDIDeviceImpl.h"
#include "../LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactory.h"

namespace MackieOfTheUnicorn::MIDI
{
	MIDIDeviceImpl::MIDIDeviceImpl(LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiFactory)
	{
		RtMidiOut = rtMidiFactory.CreateOutAbstraction();
	}

	void MIDIDeviceImpl::RegisterCallback(std::function<void(std::vector<unsigned char>)> callback)
	{
	}

	void MIDIDeviceImpl::SendMessage(std::vector<unsigned char> message)
	{
		RtMidiOut->SendMessage(&message);
	}
}
