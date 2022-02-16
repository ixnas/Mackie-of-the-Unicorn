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
} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie