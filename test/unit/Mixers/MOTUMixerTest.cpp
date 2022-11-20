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

	static std::pair<std::string, JSON::JSONValue> CreateMessage(const std::string& key, int value)
	{
		JSON::JSONValue jsonValue;
		jsonValue.Integer = value;
		std::pair<std::string, JSON::JSONValue> message = {key, jsonValue};

		return message;
	}

	static std::pair<std::string, JSON::JSONValue> CreateMessage(const std::string& key, float value)
	{
		JSON::JSONValue jsonValue;
		jsonValue.Float = value;
		std::pair<std::string, JSON::JSONValue> message = {key, jsonValue};

		return message;
	}

	static std::pair<std::string, JSON::JSONValue> CreateMessage(const std::string& key, std::string_view value)
	{
		JSON::JSONValue jsonValue;
		jsonValue.String = value;
		std::pair<std::string, JSON::JSONValue> message = {key, jsonValue};

		return message;
	}

	TEST_F(MOTUMixerTest, SetsIdCorrectly)
	{
		auto expectedId = ID;
		auto actualId = instance->GetId();

		EXPECT_EQ(actualId, expectedId);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelMuteCorrectly)
	{
		auto expectedKey = "mix/chan/5/matrix/mute";
		int expectedValue = 1;

		auto expectedMessage = CreateMessage(expectedKey, expectedValue);

		instance->SetInputChannelMute(2, 5, true);

		auto actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);

		expectedKey = "mix/chan/7/matrix/mute";
		expectedValue = 0;
		expectedMessage = CreateMessage(expectedKey, expectedValue);

		instance->SetInputChannelMute(2, 7, false);

		actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelMuteCorrectlyOnVirtualMixer)
	{
		auto expectedOrigin = ID;
		auto expectedChannel = 9;
		auto expectedOn = true;

		auto key = "mix/chan/9/matrix/mute";
		float value = 1;
		auto message = CreateMessage(key, value);

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelMuteOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelSoloCorrectly)
	{
		auto expectedKey = "mix/chan/5/matrix/solo";
		int expectedValue = 1;
		auto expectedMessage = CreateMessage(expectedKey, expectedValue);

		instance->SetInputChannelSolo(2, 5, true);

		auto actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);

		expectedKey = "mix/chan/7/matrix/solo";
		expectedValue = 0;
		expectedMessage = CreateMessage(expectedKey, expectedValue);

		instance->SetInputChannelSolo(2, 7, false);

		actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelSoloCorrectlyOnVirtualMixer)
	{
		auto expectedOrigin = ID;
		auto expectedChannel = 9;
		auto expectedOn = true;

		auto key = "mix/chan/9/matrix/solo";
		float value = 1;
		auto message = CreateMessage(key, value);

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelSoloOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelSoloChannel;
		auto actualOn = virtualMixerFake->SetInputChannelSoloOn;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelFaderCorrectlyOnVirtualMixer)
	{
		auto expectedOrigin = ID;
		auto expectedChannel = 9;
		auto expectedValue = 1;

		auto key = "mix/chan/9/matrix/fader";
		float value = 4;
		auto message = CreateMessage(key, value);

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelFaderOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelFaderChannel;
		auto actualValue = virtualMixerFake->SetInputChannelFaderValue;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualValue, expectedValue);
	}

	TEST_F(MOTUMixerTest, SetsInputChannelFaderCorrectly)
	{
		auto expectedKey = "mix/chan/5/matrix/fader";
		float expectedValue = 4;
		auto expectedMessage = CreateMessage(expectedKey, expectedValue);

		instance->SetInputChannelFader(2, 5, 1);

		auto sendMessageSize = httpDeviceFake->SendMessageMessages.size();

		ASSERT_GT(sendMessageSize, 0);

		auto actualMessage = *(httpDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMessage, expectedMessage);
	}

	TEST_F(MOTUMixerTest, IgnoresDifferentParameterSameLength)
	{
		auto key = "mix/chan/matrix/main/0/something";
		float value = 1;
		auto message = CreateMessage(key, value);

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
		auto key = "mix/chan/9/matrix/something";
		float value = 1;
		auto message = CreateMessage(key, value);

		httpDeviceFake->FakeMessage(message);

		auto actualOrigin = virtualMixerFake->SetInputChannelMuteOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_FALSE(actualOrigin.has_value());
		EXPECT_FALSE(actualChannel.has_value());
		EXPECT_FALSE(actualOn.has_value());
	}

	TEST_F(MOTUMixerTest, SetsDefaultInputChannelLabelCorrectly)
	{
		auto obankIdentifierMessage = CreateMessage("ext/obank/21/name", "Mix In");
		auto channelDefaultNameMessage = CreateMessage("ext/obank/21/ch/4/defaultName", "In 5");
		auto channelNameMessage = CreateMessage("ext/obank/21/ch/4/name", "");

		httpDeviceFake->FakeMessage(obankIdentifierMessage);

		auto* actualOrigin = &virtualMixerFake->SetInputChannelLabelOriginId;
		auto* actualChannel = &virtualMixerFake->SetInputChannelLabelChannel;
		auto* actualLabel = &virtualMixerFake->SetInputChannelLabelLabel;

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelDefaultNameMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelNameMessage);

		EXPECT_TRUE(actualOrigin->has_value());
		EXPECT_TRUE(actualChannel->has_value());
		ASSERT_TRUE(actualLabel->has_value());

		EXPECT_EQ(actualOrigin->value(), ID);
		EXPECT_EQ(actualChannel->value(), 4);
		EXPECT_EQ(actualLabel->value(), "In 5");
	}

	TEST_F(MOTUMixerTest, SetsCustomInputChannelLabelCorrectly)
	{
		auto obankIdentifierMessage = CreateMessage("ext/obank/21/name", "Mix In");
		auto channelDefaultNameMessage = CreateMessage("ext/obank/21/ch/4/defaultName", "In 5");
		auto channelNameMessage = CreateMessage("ext/obank/21/ch/4/name", "Something");

		httpDeviceFake->FakeMessage(obankIdentifierMessage);

		auto* actualOrigin = &virtualMixerFake->SetInputChannelLabelOriginId;
		auto* actualChannel = &virtualMixerFake->SetInputChannelLabelChannel;
		auto* actualLabel = &virtualMixerFake->SetInputChannelLabelLabel;

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelDefaultNameMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelNameMessage);

		EXPECT_TRUE(actualOrigin->has_value());
		EXPECT_TRUE(actualChannel->has_value());
		ASSERT_TRUE(actualLabel->has_value());

		EXPECT_EQ(actualOrigin->value(), ID);
		EXPECT_EQ(actualChannel->value(), 4);
		EXPECT_EQ(actualLabel->value(), "Something");
	}

	TEST_F(MOTUMixerTest, SetsDefaultInputChannelLabelUnordered)
	{
		auto obankIdentifierMessage = CreateMessage("ext/obank/21/name", "Mix In");
		auto channelDefaultNameMessage = CreateMessage("ext/obank/21/ch/4/defaultName", "In 5");
		auto channelNameMessage = CreateMessage("ext/obank/21/ch/4/name", "");

		httpDeviceFake->FakeMessage(channelNameMessage);

		auto* actualOrigin = &virtualMixerFake->SetInputChannelLabelOriginId;
		auto* actualChannel = &virtualMixerFake->SetInputChannelLabelChannel;
		auto* actualLabel = &virtualMixerFake->SetInputChannelLabelLabel;

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelDefaultNameMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(obankIdentifierMessage);

		EXPECT_TRUE(actualOrigin->has_value());
		EXPECT_TRUE(actualChannel->has_value());
		ASSERT_TRUE(actualLabel->has_value());

		EXPECT_EQ(actualOrigin->value(), ID);
		EXPECT_EQ(actualChannel->value(), 4);
		EXPECT_EQ(actualLabel->value(), "In 5");
	}

	TEST_F(MOTUMixerTest, SetsCustomInputChannelLabelUnordered)
	{
		auto obankIdentifierMessage = CreateMessage("ext/obank/21/name", "Mix In");
		auto channelDefaultNameMessage = CreateMessage("ext/obank/21/ch/4/defaultName", "In 5");
		auto channelNameMessage = CreateMessage("ext/obank/21/ch/4/name", "Something");

		httpDeviceFake->FakeMessage(channelNameMessage);

		auto* actualOrigin = &virtualMixerFake->SetInputChannelLabelOriginId;
		auto* actualChannel = &virtualMixerFake->SetInputChannelLabelChannel;
		auto* actualLabel = &virtualMixerFake->SetInputChannelLabelLabel;

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelDefaultNameMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(obankIdentifierMessage);

		EXPECT_TRUE(actualOrigin->has_value());
		EXPECT_TRUE(actualChannel->has_value());
		ASSERT_TRUE(actualLabel->has_value());

		EXPECT_EQ(actualOrigin->value(), ID);
		EXPECT_EQ(actualChannel->value(), 4);
		EXPECT_EQ(actualLabel->value(), "Something");
	}

	TEST_F(MOTUMixerTest, SetsCustomInputChannelLabelUnorderedAndReset)
	{
		auto obankIdentifierMessage = CreateMessage("ext/obank/21/name", "Mix In");
		auto channelDefaultNameMessage = CreateMessage("ext/obank/21/ch/4/defaultName", "In 5");
		auto channelNameMessage = CreateMessage("ext/obank/21/ch/4/name", "Something");
		auto channelNameClearMessage = CreateMessage("ext/obank/21/ch/4/name", "");

		httpDeviceFake->FakeMessage(channelNameMessage);

		auto* actualOrigin = &virtualMixerFake->SetInputChannelLabelOriginId;
		auto* actualChannel = &virtualMixerFake->SetInputChannelLabelChannel;
		auto* actualLabel = &virtualMixerFake->SetInputChannelLabelLabel;

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(channelDefaultNameMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(obankIdentifierMessage);

		EXPECT_TRUE(actualOrigin->has_value());
		EXPECT_TRUE(actualChannel->has_value());
		ASSERT_TRUE(actualLabel->has_value());

		EXPECT_EQ(actualOrigin->value(), ID);
		EXPECT_EQ(actualChannel->value(), 4);
		EXPECT_EQ(actualLabel->value(), "Something");

		httpDeviceFake->FakeMessage(channelNameClearMessage);

		EXPECT_TRUE(actualOrigin->has_value());
		EXPECT_TRUE(actualChannel->has_value());
		ASSERT_TRUE(actualLabel->has_value());

		EXPECT_EQ(actualOrigin->value(), ID);
		EXPECT_EQ(actualChannel->value(), 4);
		EXPECT_EQ(actualLabel->value(), "In 5");
	}

	TEST_F(MOTUMixerTest, SetsCustomInputChannelLabelUnorderedDifferentBank)
	{
		auto otherObankIdentifierMessage = CreateMessage("ext/obank/20/name", "Aux In");
		auto otherChannelDefaultNameMessage = CreateMessage("ext/obank/20/ch/4/defaultName", "Aux 5");
		auto otherChannelNameMessage = CreateMessage("ext/obank/20/ch/4/name", "Some other bank name");

		auto obankIdentifierMessage = CreateMessage("ext/obank/21/name", "Mix In");
		auto channelDefaultNameMessage = CreateMessage("ext/obank/21/ch/4/defaultName", "In 5");
		auto channelNameMessage = CreateMessage("ext/obank/21/ch/4/name", "Something");

		httpDeviceFake->FakeMessage(otherChannelNameMessage);

		auto* actualOrigin = &virtualMixerFake->SetInputChannelLabelOriginId;
		auto* actualChannel = &virtualMixerFake->SetInputChannelLabelChannel;
		auto* actualLabel = &virtualMixerFake->SetInputChannelLabelLabel;

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(otherChannelDefaultNameMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(otherObankIdentifierMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());

		httpDeviceFake->FakeMessage(obankIdentifierMessage);

		EXPECT_FALSE(actualOrigin->has_value());
		EXPECT_FALSE(actualChannel->has_value());
		EXPECT_FALSE(actualLabel->has_value());
	}

}