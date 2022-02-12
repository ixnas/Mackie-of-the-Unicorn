//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include <memory>
#include <optional>
#include "gtest/gtest.h"
#include "../../../fakes/LibraryAbstractions/RtMidi/RtMidiInAbstractionFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::LibraryAbstractions::RtMidi
{
	class RtMidiInAbstractionFakeTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			instance = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::RtMidiInAbstractionFake>();
			lastDeltaTime.reset();
			lastMessage.clear();
		}

		std::unique_ptr<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::RtMidiInAbstractionFake> instance;
		std::optional<double> lastDeltaTime;
		std::vector<unsigned char> lastMessage;

		void FakeCallback(double deltaTime, std::vector<unsigned char>* message, void* userData)
		{
			lastMessage.clear();
			lastMessage = *message;
			lastDeltaTime = deltaTime;
		}

		static void FakeStaticCallback(double deltaTime, std::vector<unsigned char>* message, void* userData)
		{
			auto testFixture = (RtMidiInAbstractionFakeTest*) userData;
			testFixture->FakeCallback(deltaTime, message, userData);
		}
	};

	TEST_F(RtMidiInAbstractionFakeTest, ReturnsSetPortCount)
	{
		auto expectedPortCount = 5;
		instance->PortCount = expectedPortCount;
		auto actualPortCount = instance->GetPortCount();
		EXPECT_EQ(expectedPortCount, actualPortCount);
	}

	TEST_F(RtMidiInAbstractionFakeTest, ReturnsSetPortName)
	{
		auto expectedPortName = "A port name";
		instance->PortName = expectedPortName;
		auto actualPortName = instance->GetPortName(0);
		EXPECT_EQ(expectedPortName, actualPortName);
	}

	TEST_F(RtMidiInAbstractionFakeTest, SetsCalledOpenPortArgument)
	{
		auto expectedOpenPortPort = 7;
		instance->OpenPort(expectedOpenPortPort);
		auto actualOpenPortPort = instance->OpenPortPort;
		EXPECT_EQ(actualOpenPortPort, expectedOpenPortPort);
	}

	TEST_F(RtMidiInAbstractionFakeTest, SetsCalledIgnoreTypesArguments)
	{
		auto expectedMidiSysex = true;
		auto expectedMidiTime = false;
		auto expectedMidiSense = true;

		instance->IgnoreTypes(expectedMidiSysex, expectedMidiTime, expectedMidiSense);

		auto actualMidiSysex = instance->IgnoreTypesMidiSysex;
		auto actualMidiTime = instance->IgnoreTypesMidiTime;
		auto actualMidiSense = instance->IgnoreTypesMidiSense;

		EXPECT_EQ(actualMidiSysex, expectedMidiSysex);
		EXPECT_EQ(actualMidiTime, expectedMidiTime);
		EXPECT_EQ(actualMidiSense, expectedMidiSense);
	}

	TEST_F(RtMidiInAbstractionFakeTest, SetsCallback)
	{
		auto expectedUserData = this;
		auto expectedCallback = FakeStaticCallback;
		instance->SetCallback(expectedCallback, expectedUserData);
		auto actualCallback = instance->SetCallbackCallback;
		auto actualUserData = instance->SetCallbackUserData;
		EXPECT_EQ(actualCallback, expectedCallback);
		EXPECT_EQ(actualUserData, expectedUserData);
	}

	TEST_F(RtMidiInAbstractionFakeTest, FakeMessageCallsCallback)
	{
		auto expectedDeltaTime = 24;
		std::vector<unsigned char> expectedMessage = {0, 3, 120, 34};

		instance->SetCallback(FakeStaticCallback, this);
		instance->FakeMessage(expectedDeltaTime, expectedMessage);

		auto actualDeltaTime = lastDeltaTime;
		auto actualMessage = lastMessage;

		EXPECT_EQ(actualDeltaTime, expectedDeltaTime);
		EXPECT_EQ(actualMessage, expectedMessage);
	}
}