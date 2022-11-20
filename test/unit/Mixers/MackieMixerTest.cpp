//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "gtest/gtest.h"
#include "../../../src/Mixers/MackieMixer.h"
#include "../../fakes/Mackie/MackieCompositeFake.h"
#include "../../fakes/Mixers/VirtualMixerFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mixers
{
	class MackieMixerTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			virtualMixerFake = std::make_unique<MackieOfTheUnicorn::Mixers::VirtualMixerFake>();
			mackieCompositeFake = new MackieOfTheUnicorn::Mackie::MackieCompositeFake();
			auto mackieCompositeFakePtr = std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieComposite>(mackieCompositeFake);
			instance = std::make_unique<MackieOfTheUnicorn::Mixers::MackieMixer>(mackieCompositeFakePtr, ID);
			instance->SetVirtualMixer(virtualMixerFake.get());
		}

		const int ID = 3;
		std::unique_ptr<MackieOfTheUnicorn::Mixers::VirtualMixerFake> virtualMixerFake;
		std::unique_ptr<MackieOfTheUnicorn::Mixers::MackieMixer> instance;
		MackieOfTheUnicorn::Mackie::MackieCompositeFake* mackieCompositeFake;

		template<class T>
		static long FindIndex(std::vector<T>& vector, T value)
		{
			auto it = std::find(vector.begin(), vector.end(), value);

			if (it == vector.end())
			{
				return -1;
			}

			return it - vector.begin();
		}

		void BankingTest(int oldSolo, int newSolo, int oldMute, int newMute, const std::function<void()>& bankingFunction)
		{
			instance->SetInputChannelSolo(0, oldSolo, true);
			instance->SetInputChannelMute(0, oldMute, true);

			auto soloChannelIndex = FindIndex(mackieCompositeFake->SoloChannels, oldSolo);
			auto muteChannelIndex = FindIndex(mackieCompositeFake->MuteChannels, oldMute);

			ASSERT_TRUE(mackieCompositeFake->SolosOn[soloChannelIndex]);
			ASSERT_TRUE(mackieCompositeFake->MutesOn[muteChannelIndex]);

			mackieCompositeFake->SolosOn.clear();
			mackieCompositeFake->MutesOn.clear();
			mackieCompositeFake->SoloChannels.clear();
			mackieCompositeFake->MuteChannels.clear();

			bankingFunction();

			auto oldSoloChannelIndex = FindIndex(mackieCompositeFake->SoloChannels, oldSolo);
			auto oldMuteChannelIndex = FindIndex(mackieCompositeFake->MuteChannels, oldMute);

			if (oldSoloChannelIndex != -1)
			{
				ASSERT_FALSE(mackieCompositeFake->SolosOn[oldSoloChannelIndex]);
				ASSERT_FALSE(mackieCompositeFake->MutesOn[oldMuteChannelIndex]);
			}

			auto newSoloChannelIndex = FindIndex(mackieCompositeFake->SoloChannels, newSolo);
			auto newMuteChannelIndex = FindIndex(mackieCompositeFake->MuteChannels, newMute);

			ASSERT_TRUE(mackieCompositeFake->SolosOn[newSoloChannelIndex]);
			ASSERT_TRUE(mackieCompositeFake->MutesOn[newMuteChannelIndex]);
		}
	};

	TEST_F(MackieMixerTest, HasCorrectId)
	{
		auto expectedId = ID;
		auto actualId = instance->GetId();

		EXPECT_EQ(actualId, expectedId);
	}

	TEST_F(MackieMixerTest, SetsChannelMute)
	{
		auto expectedChannel = 16;
		auto expectedOn = true;

		instance->SetInputChannelMute(0, expectedChannel, expectedOn);

		auto actualChannel = mackieCompositeFake->SetChannelMuteChannelId;
		auto actualOn = mackieCompositeFake->SetChannelMuteOn;

		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieMixerTest, SetsChannelMuteOnVirtualMixer)
	{
		auto expectedOriginId = ID;
		auto expectedChannel = 8;
		auto expectedOn = true;

		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, expectedOn);

		auto actualOriginId = virtualMixerFake->SetInputChannelMuteOriginId = expectedOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_EQ(actualOriginId, expectedOriginId);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieMixerTest, IgnoreReleaseMuteButton)
	{
		auto expectedChannel = 7;
		auto expectedOn = true;

		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, true);
		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, false);

		auto actualVirtualMixerChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualVirtualMixerOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_EQ(actualVirtualMixerChannel, expectedChannel);
		EXPECT_EQ(actualVirtualMixerOn, expectedOn);
	}

	TEST_F(MackieMixerTest, CanTurnMuteOffAgain)
	{
		auto expectedChannel = 7;
		auto expectedOn = false;

		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, true);
		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, false);
		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, true);
		instance->OnChannelMutePressed(mackieCompositeFake, expectedChannel, false);

		auto actualVirtualMixerChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualVirtualMixerOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_EQ(actualVirtualMixerChannel, expectedChannel);
		EXPECT_EQ(actualVirtualMixerOn, expectedOn);
	}

	TEST_F(MackieMixerTest, SetsChannelSolo)
	{
		auto expectedChannel = 16;
		auto expectedOn = true;

		instance->SetInputChannelSolo(0, expectedChannel, expectedOn);

		auto actualChannel = mackieCompositeFake->SetChannelSoloChannelId;
		auto actualOn = mackieCompositeFake->SetChannelSoloOn;

		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieMixerTest, SetsChannelSoloOnVirtualMixer)
	{
		auto expectedOriginId = ID;
		auto expectedChannel = 8;
		auto expectedOn = true;

		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, expectedOn);

		auto actualOriginId = virtualMixerFake->SetInputChannelSoloOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelSoloChannel;
		auto actualOn = virtualMixerFake->SetInputChannelSoloOn;

		EXPECT_EQ(actualOriginId, expectedOriginId);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieMixerTest, IgnoreReleaseSoloButton)
	{
		auto expectedChannel = 7;
		auto expectedOn = true;

		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, true);
		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, false);

		auto actualVirtualMixerChannel = virtualMixerFake->SetInputChannelSoloChannel;
		auto actualVirtualMixerOn = virtualMixerFake->SetInputChannelSoloOn;

		EXPECT_EQ(actualVirtualMixerChannel, expectedChannel);
		EXPECT_EQ(actualVirtualMixerOn, expectedOn);
	}

	TEST_F(MackieMixerTest, CanTurnSoloOffAgain)
	{
		auto expectedChannel = 7;
		auto expectedOn = false;

		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, true);
		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, false);
		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, true);
		instance->OnChannelSoloPressed(mackieCompositeFake, expectedChannel, false);

		auto actualVirtualMixerChannel = virtualMixerFake->SetInputChannelSoloChannel;
		auto actualVirtualMixerOn = virtualMixerFake->SetInputChannelSoloOn;

		EXPECT_EQ(actualVirtualMixerChannel, expectedChannel);
		EXPECT_EQ(actualVirtualMixerOn, expectedOn);
	}

	TEST_F(MackieMixerTest, BanksForwardCorrectly)
	{
		BankingTest(8, 0, 9, 1, [this] () { instance->OnBankForwardPressed(); });
	}

	TEST_F(MackieMixerTest, BanksBackwardsCorrectly)
	{
		BankingTest(8, 0, 9, 1, [this] () { instance->OnBankForwardPressed(); });
		BankingTest(0, 8, 1, 9, [this] () { instance->OnBankBackwardsPressed(); });
	}

	TEST_F(MackieMixerTest, CantBankBackwardsOutOfBounds)
	{
		auto oldSolo = 9;
		auto oldMute = 8;

		instance->SetInputChannelSolo(0, oldSolo, true);
		instance->SetInputChannelMute(0, oldMute, true);

		auto soloChannelIndex = FindIndex(mackieCompositeFake->SoloChannels, oldSolo);
		auto muteChannelIndex = FindIndex(mackieCompositeFake->MuteChannels, oldMute);

		ASSERT_TRUE(mackieCompositeFake->SolosOn[soloChannelIndex]);
		ASSERT_TRUE(mackieCompositeFake->MutesOn[muteChannelIndex]);

		mackieCompositeFake->SolosOn.clear();
		mackieCompositeFake->MutesOn.clear();
		mackieCompositeFake->SoloChannels.clear();
		mackieCompositeFake->MuteChannels.clear();

		instance->OnBankBackwardsPressed();

		auto expectedSize = 0;

		auto actualMutesSize = mackieCompositeFake->MutesOn.size();
		auto actualSolosSize = mackieCompositeFake->SolosOn.size();

		ASSERT_EQ(actualMutesSize, expectedSize);
		ASSERT_EQ(actualSolosSize, expectedSize);
	}

	TEST_F(MackieMixerTest, CantBankForwardOutOfBounds)
	{
		BankingTest(47, 7, 46, 6, [this] () {
			for (int i = 0; i < 20; i++)
			{
				instance->OnBankForwardPressed();
			}
		});
	}

	TEST_F(MackieMixerTest, SetsChannelLabelCorrectly)
	{
		auto expectedChannel = 4;
		auto expectedText = "abcdef";
		auto expectedOnBottomRow = false;

		instance->SetInputChannelLabel(1, 4, "abcdef");

		auto actualChannel = mackieCompositeFake->SetChannelTextChannel;
		auto actualText = mackieCompositeFake->SetChannelTextText;
		auto actualOnBottomRow = mackieCompositeFake->SetChannelTextOnBottomRow;

		ASSERT_TRUE(actualText.has_value());
		ASSERT_TRUE(actualChannel.has_value());
		ASSERT_TRUE(actualOnBottomRow.has_value());

		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOnBottomRow, expectedOnBottomRow);
		EXPECT_EQ(actualText, expectedText);
	}

	TEST_F(MackieMixerTest, ClearsScreenAfterInitializing)
	{
		auto actual = mackieCompositeFake->ScreenCleared;

		ASSERT_TRUE(actual);
	}

	TEST_F(MackieMixerTest, SetsChannelFaderCorrectly)
	{
		auto expectedChannel = 4;
		auto expectedValue = 0.5;

		instance->SetInputChannelFader(1, expectedChannel, expectedValue);

		auto actualChannel = mackieCompositeFake->SetChannelFaderChannel;
		auto actualValue = mackieCompositeFake->SetChannelFaderValue;

		ASSERT_TRUE(actualValue.has_value());
		ASSERT_TRUE(actualChannel.has_value());

		EXPECT_EQ(actualValue, expectedValue);
		EXPECT_EQ(actualChannel, expectedChannel);
	}

	TEST_F(MackieMixerTest, SetsChannelFaderOnVirtualMixer)
	{
		auto expectedOriginId = ID;
		auto expectedChannel = 8;
		auto expectedValue = 0.5;

		instance->OnChannelFaderMoved(mackieCompositeFake, expectedChannel, expectedValue);

		auto actualOriginId = virtualMixerFake->SetInputChannelFaderOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelFaderChannel;
		auto actualValue = virtualMixerFake->SetInputChannelFaderValue;

		EXPECT_EQ(actualOriginId, expectedOriginId);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualValue, expectedValue);
	}
}