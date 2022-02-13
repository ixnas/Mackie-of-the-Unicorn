//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "MIDIDeviceImpl.h"
#include "../LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactory.h"

namespace MackieOfTheUnicorn::MIDI
{
	void MIDIDeviceImpl::CallbackProxy(double deltaTime, std::vector<unsigned char>* message, void* userData)
	{
		auto midiReceiver = (MIDIReceiver*) userData;
		midiReceiver->MIDICallback(*message);
	}

	MIDIDeviceImpl::MIDIDeviceImpl(LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiFactory)
	{
		RtMidiOut = rtMidiFactory.CreateOutAbstraction();
		RtMidiIn = rtMidiFactory.CreateInAbstraction();
	}

	void MIDIDeviceImpl::RegisterCallback(MIDIReceiver *midiReceiver)
	{
		RtMidiIn->SetCallback(CallbackProxy, midiReceiver);
	}

	void MIDIDeviceImpl::SendMessage(std::vector<unsigned char> message)
	{
		RtMidiOut->SendMessage(&message);
	}
}
