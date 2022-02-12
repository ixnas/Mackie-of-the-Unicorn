//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include <gtest/gtest.h>
#include "../../../fakes/LibraryAbstractions/RtMidiOutAbstractionFake.h"
#include <vector>
#include <memory>

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
		std::vector<unsigned char> expectedSendMesageMessage = {0, 2, 1, 5, 2};
		instance->SendMessage(&expectedSendMesageMessage);
		auto actualSendMessageMessage = instance->SendMessageMessage;
		EXPECT_EQ(actualSendMessageMessage, expectedSendMesageMessage);
	}
}