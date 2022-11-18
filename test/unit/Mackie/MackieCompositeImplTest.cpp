//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "../../../src/Mackie/MackieCompositeImpl.h"
#include "../../fakes/Mackie/MackieDeviceFake.h"
#include "gtest/gtest.h"
#include "../../fakes/Mackie/MackieListenerFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mackie
{
	class MackieCompositeImplTest : public testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieListenerFake = std::make_unique<MackieOfTheUnicorn::Mackie::MackieListenerFake<MackieOfTheUnicorn::Mackie::MackieComposite>>();
			mackieDeviceFake = new MackieOfTheUnicorn::Mackie::MackieDeviceFake();
			auto mackieDeviceFakePtr = std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieDeviceFake>(mackieDeviceFake);
			std::vector<std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieDevice>> mackieDeviceFakes;
			mackieDeviceFakes.push_back(std::move(mackieDeviceFakePtr));
			instance = std::make_unique<MackieOfTheUnicorn::Mackie::MackieCompositeImpl>(mackieDeviceFakes);
			instance->SetMackieListener(*mackieListenerFake);
		}

		std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieListenerFake<MackieOfTheUnicorn::Mackie::MackieComposite>>
		    mackieListenerFake;
		std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieCompositeImpl> instance;
		MackieOfTheUnicorn::Mackie::MackieDeviceFake* mackieDeviceFake;
	};

	TEST_F(MackieCompositeImplTest, SetsChannelMute)
	{
		auto expectedChannelNumber = 2;
		auto expectedOn = true;

		instance->SetChannelMute(expectedChannelNumber, expectedOn);

		auto actualChannelNumber = mackieDeviceFake->SetChannelMuteChannelNumber;
		auto actualOn = mackieDeviceFake->SetChannelMuteOn;

		EXPECT_EQ(actualChannelNumber, expectedChannelNumber);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieCompositeImplTest, SetsChannelMuteOnListener)
	{
		auto expectedOrigin = instance.get();
		auto expectedChannelNumber = 2;
		auto expectedOn = true;

		mackieDeviceFake->OnChannelMutePressed(expectedChannelNumber, expectedOn);

		auto actualOrigin = mackieListenerFake->OnChannelMutePressedOrigin;
		auto actualChannelNumber = mackieListenerFake->OnChannelMutePressedChannelId;
		auto actualOn = mackieListenerFake->OnChannelMutePressedOn;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannelNumber, expectedChannelNumber);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieCompositeImplTest, SetsChannelSolo)
	{
		auto expectedChannelNumber = 2;
		auto expectedOn = true;

		instance->SetChannelSolo(expectedChannelNumber, expectedOn);

		auto actualChannelNumber = mackieDeviceFake->SetChannelSoloChannelNumber;
		auto actualOn = mackieDeviceFake->SetChannelSoloOn;

		EXPECT_EQ(actualChannelNumber, expectedChannelNumber);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieCompositeImplTest, SetsChannelText)
	{
		auto expectedChannelNumber = 4;
		auto expectedOnBottomRow = true;
		auto expectedText = "abc";

		instance->SetChannelText(expectedChannelNumber, expectedOnBottomRow, expectedText);

		auto actualChannelNumber = mackieDeviceFake->SetChannelTextChannelNumber;
		auto actualOnBottomRow = mackieDeviceFake->SetChannelTextOnBottomRow;
		auto actualText = mackieDeviceFake->SetChannelTextText;

		EXPECT_EQ(actualChannelNumber, expectedChannelNumber);
		EXPECT_EQ(actualOnBottomRow, expectedOnBottomRow);
		EXPECT_EQ(actualText, expectedText);
	}

	TEST_F(MackieCompositeImplTest, SetsChannelSoloOnListener)
	{
		auto expectedOrigin = instance.get();
		auto expectedChannelNumber = 2;
		auto expectedOn = true;

		mackieDeviceFake->OnChannelSoloPressed(expectedChannelNumber, expectedOn);

		auto actualOrigin = mackieListenerFake->OnChannelSoloPressedOrigin;
		auto actualChannelNumber = mackieListenerFake->OnChannelSoloPressedChannelId;
		auto actualOn = mackieListenerFake->OnChannelSoloPressedOn;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannelNumber, expectedChannelNumber);
		EXPECT_EQ(actualOn, expectedOn);
	}

	TEST_F(MackieCompositeImplTest, SetsBankForwardOnListener)
	{
		instance->OnBankForwardPressed();
		auto actual = mackieListenerFake->OnBankForwardPressedCalled;

		EXPECT_TRUE(actual);
	}

	TEST_F(MackieCompositeImplTest, SetsBankBackwardsOnListener)
	{
		instance->OnBankBackwardsPressed();
		auto actual = mackieListenerFake->OnBankBackwardsPressedCalled;

		EXPECT_TRUE(actual);
	}

	TEST_F(MackieCompositeImplTest, ClearsAllScreens)
	{
		instance->ClearScreen();
		auto actual = mackieDeviceFake->ScreenCleared;

		EXPECT_TRUE(actual);
	}

	TEST_F(MackieCompositeImplTest, SetsChannelFaderOnListener)
	{
		auto expectedOrigin = instance.get();
		auto expectedChannelNumber = 2;
		auto expectedValue = 0.5;

		mackieDeviceFake->OnChannelFaderMoved(expectedChannelNumber, expectedValue);

		auto actualOrigin = mackieListenerFake->OnFaderMovedOrigin;
		auto actualChannelNumber = mackieListenerFake->OnFaderMovedChannelId;
		auto actualValue = mackieListenerFake->OnFaderMovedValue;

		EXPECT_EQ(actualOrigin, expectedOrigin);
		EXPECT_EQ(actualChannelNumber, expectedChannelNumber);
		EXPECT_EQ(actualValue, expectedValue);
	}

	TEST_F(MackieCompositeImplTest, SetsChannelFader)
	{
		auto expectedChannel = 2;
		auto expectedValue = 0.5;

		instance->SetChannelFader(expectedChannel, expectedValue);

		auto actualChannel = mackieDeviceFake->OnChannelFaderMovedChannelId;
		auto actualValue = mackieDeviceFake->OnChannelFaderMovedValue;

		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualValue, expectedValue);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie