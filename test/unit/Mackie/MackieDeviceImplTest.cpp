//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#include "../../../src/Mackie/MackieDeviceImpl.h"
#include "../../fakes/MIDI/MIDIDeviceFake.h"
#include "../../fakes/Mackie/MackieListenerFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mackie
{
	class MackieDeviceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			midiDeviceFake = new MIDI::MIDIDeviceFake(0, 0);
			mackieListenerFake = std::make_unique<MackieOfTheUnicorn::Mackie::MackieListenerFake<MackieOfTheUnicorn::Mackie::MackieDevice>>();
			auto midiDeviceFakePtr = std::unique_ptr<MIDI::MIDIDevice>(midiDeviceFake);
			instance = std::make_unique<::MackieOfTheUnicorn::Mackie::MackieDeviceImpl>(midiDeviceFakePtr);
			instance->SetMackieListener(*mackieListenerFake);
		}

		std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieDeviceImpl> instance;
		std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieListenerFake<MackieOfTheUnicorn::Mackie::MackieDevice>> mackieListenerFake;
		MIDI::MIDIDeviceFake* midiDeviceFake;

		void SetsMuteChannels(bool on)
		{
			for (auto i = 0; i < 8; i++)
			{
				unsigned char byte1 = 144;
				unsigned char byte2 = 16 + i;
				unsigned char byte3 = on ? 127 : 0;
				std::vector<unsigned char> expectedMidiMessage = {byte1, byte2, byte3};

				instance->SetChannelMute(i, on);

				auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

				EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
			}
		}

		void SetsMuteChannelsOnListener(bool on)
		{
			for (auto i = 0; i < 8; i++)
			{
				unsigned char byte1 = 144;
				unsigned char byte2 = 16 + i;
				unsigned char byte3 = on ? 127 : 0;

				midiDeviceFake->FakeMessage({byte1, byte2, byte3});

				auto expectedOrigin = instance.get();
				auto expectedChannelId = i;
				auto expectedOn = on;

				auto actualOrigin = mackieListenerFake->OnChannelMutePressedOrigin;
				auto actualChannelId = mackieListenerFake->OnChannelMutePressedChannelId;
				auto actualOn = mackieListenerFake->OnChannelMutePressedOn;

				EXPECT_EQ(actualOrigin, expectedOrigin);
				EXPECT_EQ(actualChannelId, expectedChannelId);
				EXPECT_EQ(actualOn, expectedOn);
			}
		}

		void SetsSoloChannels(bool on)
		{
			for (auto i = 0; i < 8; i++)
			{
				unsigned char byte1 = 144;
				unsigned char byte2 = 8 + i;
				unsigned char byte3 = on ? 127 : 0;
				std::vector<unsigned char> expectedMidiMessage = {byte1, byte2, byte3};

				instance->SetChannelSolo(i, on);

				auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

				EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
			}
		}

		void SetsSoloChannelsOnListener(bool on)
		{
			for (auto i = 0; i < 8; i++)
			{
				unsigned char byte1 = 144;
				unsigned char byte2 = 8 + i;
				unsigned char byte3 = on ? 127 : 0;

				midiDeviceFake->FakeMessage({byte1, byte2, byte3});

				auto expectedOrigin = instance.get();
				auto expectedChannelId = i;
				auto expectedOn = on;

				auto actualOrigin = mackieListenerFake->OnChannelSoloPressedOrigin;
				auto actualChannelId = mackieListenerFake->OnChannelSoloPressedChannelId;
				auto actualOn = mackieListenerFake->OnChannelSoloPressedOn;

				EXPECT_EQ(actualOrigin, expectedOrigin);
				EXPECT_EQ(actualChannelId, expectedChannelId);
				EXPECT_EQ(actualOn, expectedOn);
			}
		}

		void SetsChannelFaders(double inputValue, std::array<char, 2> outputValue)
		{
			for (auto i = 0; i < 8; i++)
			{
				unsigned char byte1 = 0xE0 + i;
				unsigned char byte2 = outputValue[0];
				unsigned char byte3 = outputValue[1];
				std::vector<unsigned char> expectedMidiMessage = {byte1, byte2, byte3};

				instance->SetChannelFader(i, inputValue);

				auto sendMessagesSize = midiDeviceFake->SendMessageMessages.size();

				ASSERT_GT(sendMessagesSize, 0);

				auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

				EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
			}
		}

	};

	TEST_F(MackieDeviceImplTest, SetsChannelMutesOn)
	{
		SetsMuteChannels(true);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelMutesOff)
	{
		SetsMuteChannels(false);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelMutesOnOnListener)
	{
		SetsMuteChannelsOnListener(true);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelMutesOffOnListener)
	{
		SetsMuteChannelsOnListener(false);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelSolosOn)
	{
		SetsSoloChannels(true);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelSolosOff)
	{
		SetsSoloChannels(false);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelSolosOnOnListener)
	{
		SetsSoloChannelsOnListener(true);
	}

	TEST_F(MackieDeviceImplTest, SetsChannelSolosOffOnListener)
	{
		SetsSoloChannelsOnListener(false);
	}

	TEST_F(MackieDeviceImplTest, IgnoresChannelsAbove7)
	{
		instance->SetChannelMute(8, true);
		instance->SetChannelSolo(8, true);

		auto gotMessages = !midiDeviceFake->SendMessageMessages.empty();

		EXPECT_FALSE(gotMessages);
	}

	TEST_F(MackieDeviceImplTest, SetsBankForwardOnListener)
	{
		std::vector<unsigned char> midiMessage = { 0x90, 0x2F, 0x7F };
		midiDeviceFake->FakeMessage(midiMessage);
		auto setBankForwardOnListener = mackieListenerFake->OnBankForwardPressedCalled;

		EXPECT_TRUE(setBankForwardOnListener);
	}

	TEST_F(MackieDeviceImplTest, SetsBankBackwardsOnListener)
	{
		std::vector<unsigned char> midiMessage = { 0x90, 0x2E, 0x7F };
		midiDeviceFake->FakeMessage(midiMessage);
		auto setBankBackwardsOnListener = mackieListenerFake->OnBankBackwardsPressedCalled;

		EXPECT_TRUE(setBankBackwardsOnListener);
	}

	TEST_F(MackieDeviceImplTest, SetsTextShortOnChannel0)
	{
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00, 'a', 'a', 'a', ' ', ' ', ' ', 0xF7 };
		instance->SetChannelText(0, false, "aaa");
		auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
	}

	TEST_F(MackieDeviceImplTest, SetsTextShortOnChannel0OnBottomRow)
	{
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38, 'a', 'a', 'a', ' ', ' ', ' ', 0xF7 };
		instance->SetChannelText(0, true, "aaa");
		auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
	}

	TEST_F(MackieDeviceImplTest, SetsTextShortOnChannel4)
	{
		unsigned char start = 7 * 4;
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, start, 'a', 'a', 'a', ' ', ' ', ' ', 0xF7 };
		instance->SetChannelText(4, false, "aaa");
		auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
	}

	TEST_F(MackieDeviceImplTest, SetsTextShortOnChannel4OnBottomRow)
	{
		unsigned char start = 0x38 + 7 * 4;
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, start, 'a', 'a', 'a', ' ', ' ', ' ', 0xF7 };
		instance->SetChannelText(4, true, "aaa");
		auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
	}

	TEST_F(MackieDeviceImplTest, SetsTextLongOnChannel0)
	{
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00, 'a', 'a', 'a', 'a', 'a', 'a', 0xF7 };
		instance->SetChannelText(0, false, "aaaaaaaaaaaa");
		auto actualMidiMessage = *(midiDeviceFake->SendMessageMessages.end() - 1);

		EXPECT_EQ(actualMidiMessage, expectedMidiMessage);
	}

	TEST_F(MackieDeviceImplTest, SetsTextOnInvalidChannel)
	{
		instance->SetChannelText(8, false, "aaa");

		auto actualSize = midiDeviceFake->SendMessageMessages.size();
		auto expectedSize = 0;

		EXPECT_EQ(actualSize, expectedSize);
	}

	TEST_F(MackieDeviceImplTest, ClearsScreenCorrectly)
	{
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00 };
		for (int i = 0; i < 112; i++)
		{
			expectedMidiMessage.push_back(' ');
		}

		expectedMidiMessage.push_back(0xF7);

		instance->ClearScreen();

		auto actualSize = midiDeviceFake->SendMessageMessages.size();
		ASSERT_EQ(actualSize, 1);

		auto actualMessage = midiDeviceFake->SendMessageMessages[0];
		ASSERT_EQ(actualMessage, expectedMidiMessage);
	}

	TEST_F(MackieDeviceImplTest, ClearsScreenCorrectlyMultipleTimes)
	{
		std::vector<unsigned char> expectedMidiMessage { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00 };
		for (int i = 0; i < 112; i++)
		{
			expectedMidiMessage.push_back(' ');
		}

		expectedMidiMessage.push_back(0xF7);

		for (auto i = 0; i < 2; i++)
		{
			instance->ClearScreen();

			auto actualSize = midiDeviceFake->SendMessageMessages.size();
			ASSERT_EQ(actualSize, 1);

			auto actualMessage = midiDeviceFake->SendMessageMessages[0];
			ASSERT_EQ(actualMessage, expectedMidiMessage);

			midiDeviceFake->SendMessageMessages.clear();
		}
	}

	TEST_F(MackieDeviceImplTest, SetsChannelFadersToEighth)
	{
		SetsChannelFaders((double)1 / 8, {0x7F, 0x0F});
	}

	TEST_F(MackieDeviceImplTest, SetsChannelFadersToSevenEighth)
	{
		SetsChannelFaders((double)1 / 8 * 7, {0x7F, 0x6F});
	}

	TEST_F(MackieDeviceImplTest, SetsFaderOnListener)
	{
		auto expectedOrigin = instance.get();
		auto expectedChannelId = 4;
		double expectedValue = 0;

		std::vector<unsigned char> midiMessage = { 0xE4, 0x00, 0x00 };
		midiDeviceFake->FakeMessage(midiMessage);

		auto actualOrigin = mackieListenerFake->OnFaderMovedOrigin;
		auto actualChannelId = mackieListenerFake->OnFaderMovedChannelId;
		auto actualValue = mackieListenerFake->OnFaderMovedValue;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannelId, expectedChannelId);
		EXPECT_EQ(actualValue, expectedValue);
	}

} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie