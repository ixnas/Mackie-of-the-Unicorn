//
// Created by Sjoerd Scheffer on 13/02/2022.
//

#include "../../../../src/MIDI/Factories/MIDIDeviceFactoryImpl.h"
#include "../../../fakes/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Unit::MIDI::Factories
{
	class MIDIDeviceFactoryImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			rtMidiAbstractionFactoryFake = std::make_unique<LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake>();
			instance = std::make_unique<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryImpl>(*rtMidiAbstractionFactoryFake);
		}

		std::unique_ptr<LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake> rtMidiAbstractionFactoryFake;
		std::unique_ptr<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryImpl> instance;
	};

	TEST_F(MIDIDeviceFactoryImplTest, ReturnsMIDIDevice)
	{
		auto midiDevice = instance->Create(0, 0);

		EXPECT_NE(midiDevice.get(), nullptr);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::MIDI::Factories
