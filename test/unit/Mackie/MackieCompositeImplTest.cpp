//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "../../../src/Mackie/MackieCompositeImpl.h"
#include "../../fakes/Mackie/MackieDeviceFake.h"
#include "gtest/gtest.h"
#include <memory>
#include <vector>

namespace MackieOfTheUnicorn::Tests::Unit::Mackie
{
	class MackieCompositeImplTest : public testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieDeviceFake = new MackieOfTheUnicorn::Mackie::MackieDeviceFake();
			auto mackieDeviceFakePtr = std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieDeviceFake>(mackieDeviceFake);
			std::vector<std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieDevice>> mackieDeviceFakes;
			mackieDeviceFakes.push_back(std::move(mackieDeviceFakePtr));
			instance = std::make_unique<MackieOfTheUnicorn::Mackie::MackieCompositeImpl>(mackieDeviceFakes);
		}

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
} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie