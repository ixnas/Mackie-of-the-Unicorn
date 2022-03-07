//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "../../../src/Mixers/VirtualMixerImpl.h"
#include "../../fakes/Mixers/LinkedMixerFake.h"
#include <gtest/gtest.h>

namespace MackieOfTheUnicorn::Tests::Unit::Mixers
{
	class VirtualMixerImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			std::vector<std::unique_ptr<MackieOfTheUnicorn::Mixers::LinkedMixer>> linkedMixerPtrs;

			for(auto i = 0; i < 3; i++)
			{
				auto linkedMixerFakeInstance = std::make_unique<MackieOfTheUnicorn::Mixers::LinkedMixerFake>();
				linkedMixerFakeInstance->Id = i;
				linkedMixerFakes.push_back(linkedMixerFakeInstance.get());
				linkedMixerPtrs.push_back(std::move(linkedMixerFakeInstance));
			}

			instance = std::make_unique<MackieOfTheUnicorn::Mixers::VirtualMixerImpl>(linkedMixerPtrs);
		}

		std::vector<MackieOfTheUnicorn::Mixers::LinkedMixerFake*> linkedMixerFakes;
		std::unique_ptr<MackieOfTheUnicorn::Mixers::VirtualMixerImpl> instance;
	};

	TEST_F(VirtualMixerImplTest, AssignsInstanceToLinkedMixers)
	{
		auto expectedPtr = instance.get();
		for (const auto& linkedMixerFake : linkedMixerFakes)
		{
			auto actualPtr = linkedMixerFake->VirtualMixer;
			EXPECT_EQ(actualPtr, expectedPtr);
		}
	}

	TEST_F(VirtualMixerImplTest, SetInputChannelMuteCallsOtherMixers)
	{
		auto expectedOrigin = 1;
		auto expectedChannel = 24;
		auto expectedOn = true;

		instance->SetInputChannelMute(expectedOrigin, expectedChannel, expectedOn);

		for (const auto& linkedMixerFake : linkedMixerFakes)
		{
			auto actualOrigin = linkedMixerFake->SetInputChannelMuteOriginId;
			auto actualChannel = linkedMixerFake->SetInputChannelMuteChannel;
			auto actualOn = linkedMixerFake->SetInputChannelMuteOn;

			if (expectedOrigin == linkedMixerFake->Id)
			{
				EXPECT_FALSE(actualOrigin.has_value());
				EXPECT_FALSE(actualChannel.has_value());
				EXPECT_FALSE(actualOn.has_value());
			}
			else
			{
				EXPECT_EQ(expectedOn, actualOn);
				EXPECT_EQ(expectedChannel, actualChannel);
				EXPECT_EQ(expectedOrigin, actualOrigin);
			}
		}
	}

	TEST_F(VirtualMixerImplTest, SetInputChannelSoloCallsOtherMixers)
	{
		auto expectedOrigin = 1;
		auto expectedChannel = 24;
		auto expectedOn = true;

		instance->SetInputChannelSolo(expectedOrigin, expectedChannel, expectedOn);

		for (const auto& linkedMixerFake : linkedMixerFakes)
		{
			auto actualOrigin = linkedMixerFake->SetInputChannelSoloOriginId;
			auto actualChannel = linkedMixerFake->SetInputChannelSoloChannel;
			auto actualOn = linkedMixerFake->SetInputChannelSoloOn;

			if (expectedOrigin == linkedMixerFake->Id)
			{
				EXPECT_FALSE(actualOrigin.has_value());
				EXPECT_FALSE(actualChannel.has_value());
				EXPECT_FALSE(actualOn.has_value());
			}
			else
			{
				EXPECT_EQ(expectedOn, actualOn);
				EXPECT_EQ(expectedChannel, actualChannel);
				EXPECT_EQ(expectedOrigin, actualOrigin);
			}
		}
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::Mixers