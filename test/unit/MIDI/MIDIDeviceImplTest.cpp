//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include <gtest/gtest.h>
#include <memory>
#include "../../../src/MIDI/MIDIDeviceImpl.h"
#include "../../fakes/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::MIDI
{
	class MIDIDeviceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			rtMidiFactory = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake>();
			instance = std::make_unique<MackieOfTheUnicorn::MIDI::MIDIDeviceImpl>(*rtMidiFactory);
		}

		std::unique_ptr<MackieOfTheUnicorn::MIDI::MIDIDeviceImpl> instance;
		std::unique_ptr<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake> rtMidiFactory;
	};

	TEST_F(MIDIDeviceImplTest, SendsMessages)
	{
		std::vector<unsigned char> expectedMessage1 = {0, 5, 2, 3};
		std::vector<unsigned char> expectedMessage2 = {3, 2, 2, 5};

		instance->SendMessage(expectedMessage1);
		instance->SendMessage(expectedMessage2);

		auto outAbstractionInstance = rtMidiFactory->ReturnedOutAbstractions[0];

		auto actualMessage1 = outAbstractionInstance->SendMessageMessages[0];
		auto actualMessage2 = outAbstractionInstance->SendMessageMessages[1];

		EXPECT_EQ(expectedMessage1, actualMessage1);
		EXPECT_EQ(expectedMessage2, actualMessage2);
	}

	TEST_F(MIDIDeviceImplTest, ListensToDevice)
	{
	}

} // namespace MackieOfTheUnicorn::Tests::Unit::MIDI
