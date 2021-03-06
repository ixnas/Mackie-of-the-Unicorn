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
} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie