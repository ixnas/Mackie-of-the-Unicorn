//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#include "MIDIDeviceFactoryImpl.h"
#include "../MIDIDeviceImpl.h"

namespace MackieOfTheUnicorn::MIDI::Factories
{
	MIDIDeviceFactoryImpl::MIDIDeviceFactoryImpl(
		LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiAbstractionFactory) : RtMidiAbstractionFactory(&rtMidiAbstractionFactory)
	{
	}
	std::unique_ptr<MIDIDevice> MIDIDeviceFactoryImpl::Create(int inputId, int outputId)
	{
		return std::make_unique<MIDIDeviceImpl>(*RtMidiAbstractionFactory, inputId, outputId);
	}
}
