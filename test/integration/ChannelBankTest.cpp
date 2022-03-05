//
// Created by Sjoerd Scheffer on 05/03/2022.
//

#include "ApplicationContainer.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Integration
{
	class ChannelBankTest : public ::testing::Test
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
	};

	TEST_F(ChannelBankTest, BanksForwardCorrectly)
	{
		auto curlIn = wrapper->CurlInAbstractionFake;
		auto rtMidiOut = wrapper->RtMidiOutAbstractionFake;
		auto rtMidiIn = wrapper->RtMidiInAbstractionFake;

		std::ostringstream motuMessage;
		motuMessage << "{\"mix/chan/0/matrix/solo\":1.000000,\n"
		            << "\"mix/chan/1/matrix/mute\":1.000000,\n"
		            << "\"mix/chan/15/matrix/mute\":1.000000,\n"
		            << "\"mix/chan/16/matrix/solo\":1.000000}\n";
		auto motuMessageStr = motuMessage.str();

		auto oldSize = rtMidiOut->SendMessageMessages.size();
		curlIn->FakeHasChangedMessage(motuMessageStr);

		auto startTime = std::chrono::system_clock::now();
		while (rtMidiOut->SendMessageMessages.size() != oldSize + 2)
		{
			auto endTime = std::chrono::system_clock::now();
			auto diff = endTime - startTime;
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
			if (duration > 0)
			{
				FAIL() << "Incoming channel mutes/solos not received.";
			}
		}

		rtMidiOut->SendMessageMessages.clear();
		oldSize = rtMidiOut->SendMessageMessages.size();

		std::vector<unsigned char> message = {0x90, 0x2F, 0x7F};
		rtMidiIn->FakeMessage(0, message);

		startTime = std::chrono::system_clock::now();
		while (rtMidiOut->SendMessageMessages.size() != oldSize + 4)
		{
			auto endTime = std::chrono::system_clock::now();
			auto diff = endTime - startTime;
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
			if (duration > 0)
			{
				FAIL() << "Outgoing LED switches not sent.";
			}
		}

		auto containsUnSolo0 = std::any_of(
		    rtMidiOut->SendMessageMessages.begin(),
		    rtMidiOut->SendMessageMessages.end(),
		    [] (auto el) { return el == std::vector<unsigned char> {144, 8, 0}; });

		auto containsMute0 = std::any_of(
			rtMidiOut->SendMessageMessages.begin(),
			rtMidiOut->SendMessageMessages.end(),
			[] (auto el) { return el == std::vector<unsigned char> {144, 16, 127}; });

		auto containsUnMute1 = std::any_of(
			rtMidiOut->SendMessageMessages.begin(),
			rtMidiOut->SendMessageMessages.end(),
			[] (auto el) { return el == std::vector<unsigned char> {144, 17, 0}; });

		auto containsSolo1 = std::any_of(
			rtMidiOut->SendMessageMessages.begin(),
			rtMidiOut->SendMessageMessages.end(),
			[] (auto el) { return el == std::vector<unsigned char> {144, 9, 127}; });

		auto expectedSendMessagesSize = 4;
		auto actualSendMessagesSize = rtMidiOut->SendMessageMessages.size();

		ASSERT_TRUE(containsUnSolo0);
		ASSERT_TRUE(containsMute0);
		ASSERT_TRUE(containsUnMute1);
		ASSERT_TRUE(containsSolo1);

		ASSERT_EQ(actualSendMessagesSize, expectedSendMessagesSize);
	}
} // namespace MackieOfTheUnicorn::Tests::Integration