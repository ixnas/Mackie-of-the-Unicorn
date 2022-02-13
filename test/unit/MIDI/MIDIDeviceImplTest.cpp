//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include <gtest/gtest.h>
#include <memory>
#include "../../../src/MIDI/MIDIDeviceImpl.h"
#include "../../../src/MIDI/MIDIReceiver.h"
#include "../../fakes/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::MIDI
{
	class MIDIDeviceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			rtMidiFactory = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake>();
			instance = std::make_unique<MackieOfTheUnicorn::MIDI::MIDIDeviceImpl>(*rtMidiFactory, INPUT_ID, OUTPUT_ID);
		}

		const int INPUT_ID = 4;
		const int OUTPUT_ID = 3;

		std::unique_ptr<MackieOfTheUnicorn::MIDI::MIDIDeviceImpl> instance;
		std::unique_ptr<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake> rtMidiFactory;
	};

	class Receiver : public MackieOfTheUnicorn::MIDI::MIDIReceiver
	{
	  public:
		std::vector<unsigned char> lastMessage;
		void MIDICallback(std::vector<unsigned char>& message) override
		{
			lastMessage = message;
		}
	};

	TEST_F(MIDIDeviceImplTest, OpensRtMidiPorts)
	{
		auto expectedInputId = INPUT_ID;
		auto expectedOutputId = OUTPUT_ID;

		auto actualInputId = rtMidiFactory->ReturnedInAbstractions[0]->OpenPortPort;
		auto actualOutputId = rtMidiFactory->ReturnedOutAbstractions[0]->OpenPortPort;

		EXPECT_EQ(expectedInputId, actualInputId);
		EXPECT_EQ(expectedOutputId, actualOutputId);
	}

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
		std::vector<unsigned char> expectedMessage = {2, 3, 2, 7, 5};
		Receiver receiver;
		instance->RegisterCallback(&receiver);

		auto inAbstractionInstance = rtMidiFactory->ReturnedInAbstractions[0];

		inAbstractionInstance->FakeMessage(0, expectedMessage);
		auto actualMessage = receiver.lastMessage;

		EXPECT_EQ(actualMessage, expectedMessage);
	}

} // namespace MackieOfTheUnicorn::Tests::Unit::MIDI
