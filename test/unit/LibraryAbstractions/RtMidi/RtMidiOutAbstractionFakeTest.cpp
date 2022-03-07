//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "../../../fakes/LibraryAbstractions/RtMidi/RtMidiOutAbstractionFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Unit::LibraryAbstractions::RtMidi
{
	class RtMidiOutAbstractionFakeTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			instance = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::RtMidiOutAbstractionFake>();
		}

		std::unique_ptr<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::RtMidiOutAbstractionFake> instance;
	};

	TEST_F(RtMidiOutAbstractionFakeTest, ReturnsSetPortCount)
	{
		auto expectedPortCount = 5;
		instance->PortCount = expectedPortCount;
		auto actualPortCount = instance->GetPortCount();
		EXPECT_EQ(expectedPortCount, actualPortCount);
	}

	TEST_F(RtMidiOutAbstractionFakeTest, ReturnsSetPortName)
	{
		auto expectedPortName = "A port name";
		instance->PortName = expectedPortName;
		auto actualPortName = instance->GetPortName(0);
		EXPECT_EQ(expectedPortName, actualPortName);
	}

	TEST_F(RtMidiOutAbstractionFakeTest, SetsCalledOpenPortArgument)
	{
		auto expectedOpenPortPort = 7;
		instance->OpenPort(expectedOpenPortPort);
		auto actualOpenPortPort = instance->OpenPortPort;
		EXPECT_EQ(actualOpenPortPort, expectedOpenPortPort);
	}

	TEST_F(RtMidiOutAbstractionFakeTest, SetsCalledSendMessageArgument)
	{
		std::vector<std::vector<unsigned char>> expectedSendMesageMessages = {{0, 2, 1, 5, 2}, {0, 2, 3, 3, 2, 1}};

		for(auto i = 0; i < expectedSendMesageMessages.size(); i++)
		{
			instance->SendMessage(&expectedSendMesageMessages[i]);
			auto actualSendMessageMessage = instance->SendMessageMessages[i];
			EXPECT_EQ(actualSendMessageMessage, expectedSendMesageMessages[i]);
		}
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::LibraryAbstractions::RtMidi