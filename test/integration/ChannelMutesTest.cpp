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

		std::unique_ptr<ApplicationContainerWrapper> wrapper;
		ApplicationContainer* instance;
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
			auto hasPerformed = curlOut->Performed;

			EXPECT_EQ(actualJSONMessage, expectedJSONMessage);
			EXPECT_TRUE(hasPerformed);
		};

		for (int i = 0; i < 8; i++)
		{
			switchMute(i, true);
			switchMute(i, false);
		}
	}
} // namespace MackieOfTheUnicorn::Tests::Integration