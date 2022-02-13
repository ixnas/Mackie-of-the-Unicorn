//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#include "gtest/gtest.h"
#include "../../fakes/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryFake.h"
#include "../../fakes/MIDI/Factories/MIDIDeviceFactoryFake.h"
#include "../../../src/MIDI/MIDIServiceImpl.h"

namespace MackieOfTheUnicorn::Tests::Unit::MIDI
{
	class MIDIServiceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			rtMidiAbstractionFactory =
			    std::make_unique<LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake>();
			midiDeviceFactory = std::make_unique<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryFake>();
			instance = std::make_unique<MackieOfTheUnicorn::MIDI::MIDIServiceImpl>(*rtMidiAbstractionFactory,
			                                                                       *midiDeviceFactory);
		}

		std::unique_ptr<MackieOfTheUnicorn::MIDI::MIDIServiceImpl> instance;
		std::unique_ptr<LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake> rtMidiAbstractionFactory;
		std::unique_ptr<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryFake> midiDeviceFactory;
	};

	TEST_F(MIDIServiceImplTest, ReturnsInputDevices)
	{
		auto portCount = 1;
		auto portId = 0;
		auto portName = "something";

		std::map<int, std::string> expectedInputDevices = {{portId, portName}};

		rtMidiAbstractionFactory->ReturnedInAbstractions[0]->PortCount = portCount;
		rtMidiAbstractionFactory->ReturnedInAbstractions[0]->PortName = portName;

		auto actualInputDevices = instance->GetInputDevices();

		EXPECT_EQ(expectedInputDevices, actualInputDevices);
	}

	TEST_F(MIDIServiceImplTest, ReturnsOutputDevices)
	{
		auto portCount = 1;
		auto portId = 0;
		auto portName = "out";

		std::map<int, std::string> expectedOutputDevices = {{portId, portName}};

		rtMidiAbstractionFactory->ReturnedOutAbstractions[0]->PortCount = portCount;
		rtMidiAbstractionFactory->ReturnedOutAbstractions[0]->PortName = portName;

		auto actualOutputDevices = instance->GetOutputDevices();

		EXPECT_EQ(expectedOutputDevices, actualOutputDevices);
	}

	TEST_F(MIDIServiceImplTest, ReturnsMIDIDevice)
	{
		auto actualMidiDevice = instance->GetMIDIDevice(0, 0);

		EXPECT_NE(actualMidiDevice.get(), nullptr);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::MIDI
