//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include <gtest/gtest.h>
#include "../../../src/Mixers/MOTUMixer.h"
#include "../../fakes/HTTP/HTTPDeviceFake.h"
#include "../../fakes/Mixers/VirtualMixerFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mixers
{
	class MOTUMixerTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			auto httpDeviceFakePtr = std::make_unique<MackieOfTheUnicorn::HTTP::HTTPDeviceFake>();
			virtualMixerFake = std::make_unique<MackieOfTheUnicorn::Mixers::VirtualMixerFake>();
			httpDeviceFake = httpDeviceFakePtr.get();
			instance = std::make_unique<MackieOfTheUnicorn::Mixers::MOTUMixer>(std::move(httpDeviceFakePtr), ID);
			instance->SetVirtualMixer(virtualMixerFake.get());
		}

		const int ID = 3;
		HTTP::HTTPDeviceFake* httpDeviceFake;
		std::unique_ptr<MackieOfTheUnicorn::Mixers::VirtualMixerFake> virtualMixerFake;
		std::unique_ptr<MackieOfTheUnicorn::Mixers::MOTUMixer> instance;
	};

	TEST_F(MOTUMixerTest, SetsIdCorrectly)
	{
		auto expectedId = ID;
		auto actualId = instance->GetId();

		EXPECT_EQ(actualId, expectedId);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelMuteCorrectly)
	{
		std::string expectedKey = "mix/chan/5/matrix/mute";
		JSON::JSONValue expectedValue;
		expectedValue.Integer = 1;
		std::pair<std::string, JSON::JSONValue> expectedMessage = {expectedKey, expectedValue};

		instance->SetInputChannelMute(2, 5, true);

		auto actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);

		expectedKey = "mix/chan/7/matrix/mute";
		expectedValue.Integer = 0;
		expectedMessage = {expectedKey, expectedValue};

		instance->SetInputChannelMute(2, 7, false);

		actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelMuteCorrectlyOnVirtualMixer)
	{
		auto expectedOrigin = ID;
		auto expectedChannel = 9;
		auto expectedOn = true;

		std::string key = "mix/chan/9/matrix/mute";
		JSON::JSONValue value;
		value.Float = 1;
		std::pair<std::string, JSON::JSONValue> message = {key, value};

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelMuteOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MOTUMixerTest, IgnoresDifferentParameterSameLength)
	{
		std::string key = "mix/chan/matrix/main/0/send";
		JSON::JSONValue value;
		value.Float = 1;
		std::pair<std::string, JSON::JSONValue> message = {key, value};

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelMuteOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_FALSE(actualOrigin.has_value());
		EXPECT_FALSE(actualChannel.has_value());
		EXPECT_FALSE(actualOn.has_value());
	}

	TEST_F(MOTUMixerTest, IgnoresDifferentParameterDifferentLength)
	{
		std::string key = "mix/chan/9/matrix/solo";
		JSON::JSONValue value;
		value.Float = 1;
		std::pair<std::string, JSON::JSONValue> message = {key, value};

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelMuteOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_FALSE(actualOrigin.has_value());
		EXPECT_FALSE(actualChannel.has_value());
		EXPECT_FALSE(actualOn.has_value());
	}
}