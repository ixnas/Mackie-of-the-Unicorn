//
// Created by Sjoerd Scheffer on 20/02/2022.
//

#include "ApplicationContainer.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Integration
{
	class ChannelMutesTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			wrapper = GetApplicationContainerWrapper();
			instance = &wrapper->ApplicationContainer;
		}

		void TearDown() override
		{
			wrapper.reset(nullptr);
		}

		std::unique_ptr<ApplicationContainerWrapper> wrapper;
		ApplicationContainer* instance;

		void MOTUCanSwitchFirst8Channels(bool expectedOn)
		{
			for (int i = 0; i < 8; i++)
			{
				auto curlIn = wrapper->CurlInAbstractionFake;
				auto rtMidiOut = wrapper->RtMidiOutAbstractionFake;
				std::ostringstream stringStream;
				stringStream << "{\"mix/chan/" << i << "/matrix/mute\":" << (expectedOn ? "1.000000" : "0.000000")
				             << "}";
				auto jsonMessage = stringStream.str();

				std::vector<unsigned char> expectedMIDIMessage = {144, (unsigned char)(16 + i),
				                                                  (unsigned char)(expectedOn ? 127 : 0)};

				auto oldSize = rtMidiOut->SendMessageMessages.size();
				curlIn->FakeHasChangedMessage(jsonMessage);
				auto startTime = std::chrono::system_clock::now();
				while (rtMidiOut->SendMessageMessages.size() == oldSize)
				{
					auto endTime = std::chrono::system_clock::now();
					auto diff = endTime - startTime;
					auto duration = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
					if (duration > 0)
					{
						FAIL();
					}
				}

				auto actualMIDIMessage = *(rtMidiOut->SendMessageMessages.end() - 1);
				EXPECT_EQ(actualMIDIMessage, expectedMIDIMessage);
			}
		}
	};

	TEST_F(ChannelMutesTest, MackieCanSwitchFirst8Mutes)
	{
		auto curlOut = wrapper->CurlOutAbstractionFake;
		auto rtMidiIn = wrapper->RtMidiInAbstractionFake;

		auto switchMute = [&curlOut, &rtMidiIn](int i, bool expectedOn) {
			std::ostringstream stringStream;
			stringStream << "json={\"mix/chan/" << i << "/matrix/mute\":" << (expectedOn ? 1 : 0) << "}";
			auto expectedJSONMessage = stringStream.str();

			std::vector<unsigned char> message = {144, (unsigned char)(16 + i), 127};
			rtMidiIn->FakeMessage(0, message);
			message = {144, (unsigned char)(16 + i), 0};
			rtMidiIn->FakeMessage(0, message);

			auto actualJSONMessage = curlOut->SetPostDataPostData;

			EXPECT_EQ(actualJSONMessage, expectedJSONMessage);
		};

		for (int i = 0; i < 8; i++)
		{
			switchMute(i, true);
			switchMute(i, false);
		}
	}

	TEST_F(ChannelMutesTest, MOTUCanSwitchFirst8ChannelsOn)
	{
		MOTUCanSwitchFirst8Channels(true);
	}

	TEST_F(ChannelMutesTest, MOTUCanSwitchFirst8ChannelsOff)
	{
		MOTUCanSwitchFirst8Channels(false);
	}
} // namespace MackieOfTheUnicorn::Tests::Integration