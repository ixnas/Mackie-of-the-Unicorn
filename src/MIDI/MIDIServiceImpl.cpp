//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#include "MIDIServiceImpl.h"
#include "Factories/MIDIDeviceFactory.h"

namespace MackieOfTheUnicorn::MIDI
{
	MIDIServiceImpl::MIDIServiceImpl(
	    LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiAbstractionFactory,
	    Factories::MIDIDeviceFactory& midiDeviceFactory)
	: MIDIDeviceFactory(&midiDeviceFactory)
	{
		RtMidiIn = rtMidiAbstractionFactory.CreateInAbstraction();
		RtMidiOut = rtMidiAbstractionFactory.CreateOutAbstraction();
	}

	std::map<int, std::string> MIDIServiceImpl::GetInputDevices()
	{
		auto portCount = RtMidiIn->GetPortCount();
		std::map<int, std::string> inputDevices;

		for (auto i = 0; i < portCount; i++)
		{
			auto inputDeviceName = RtMidiIn->GetPortName(i);
			inputDevices.insert({i, inputDeviceName});
		}

		return inputDevices;
	}

	std::map<int, std::string> MIDIServiceImpl::GetOutputDevices()
	{
		auto portCount = RtMidiOut->GetPortCount();
		std::map<int, std::string> outputDevices;

		for (auto i = 0; i < portCount; i++)
		{
			auto outputDeviceName = RtMidiOut->GetPortName(i);
			outputDevices.insert({i, outputDeviceName});
		}

		return outputDevices;
	}

	std::unique_ptr<MIDIDevice> MIDIServiceImpl::GetMIDIDevice(int inputId, int outputId)
	{
		return MIDIDeviceFactory->Create(inputId, outputId);
	}
}
