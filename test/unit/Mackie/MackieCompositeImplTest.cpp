//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "../../../src/Mackie/MackieCompositeImpl.h"
#include "../../fakes/Mackie/MackieDeviceFake.h"
#include "gtest/gtest.h"
#include "../../fakes/Mackie/MackieListenerFake.h"
#include <memory>
#include <vector>

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

		mackieDeviceFake->SetChannelMute(expectedChannelNumber, expectedOn);

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

	TEST_F(MackieCompositeImplTest, SetsChannelSoloOnListener)
	{
		auto expectedOrigin = instance.get();
		auto expectedChannelNumber = 2;
		auto expectedOn = true;

		mackieDeviceFake->SetChannelSolo(expectedChannelNumber, expectedOn);

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
} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie