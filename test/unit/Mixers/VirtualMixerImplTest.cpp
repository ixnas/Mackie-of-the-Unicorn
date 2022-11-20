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

	TEST_F(VirtualMixerImplTest, SetInputChannelLabelsOnOtherMixers)
	{
		auto expectedOrigin = 1;
		auto expectedChannel = 24;
		auto expectedLabel = "Something";

		instance->SetInputChannelLabel(expectedOrigin, expectedChannel, expectedLabel);

		for (const auto& linkedMixerFake : linkedMixerFakes)
		{
			auto actualOrigin = linkedMixerFake->SetInputChannelLabelOriginId;
			auto actualChannel = linkedMixerFake->SetInputChannelLabelChannel;
			auto actualLabel = linkedMixerFake->SetInputChannelLabelLabel;

			if (expectedOrigin == linkedMixerFake->Id)
			{
				EXPECT_FALSE(actualOrigin.has_value());
				EXPECT_FALSE(actualChannel.has_value());
				EXPECT_FALSE(actualLabel.has_value());
			}
			else
			{
				EXPECT_EQ(expectedLabel, actualLabel);
				EXPECT_EQ(expectedChannel, actualChannel);
				EXPECT_EQ(expectedOrigin, actualOrigin);
			}
		}
	}

	TEST_F(VirtualMixerImplTest, SetsInputChannelFadersOnOtherMixers)
	{
		auto expectedOrigin = 1;
		auto expectedChannel = 5;
		auto expectedValue = 0.5;

		instance->SetInputChannelFader(expectedOrigin, expectedChannel, expectedValue);

		for (const auto& linkedMixerFake : linkedMixerFakes)
		{
			auto actualOrigin = linkedMixerFake->SetInputChannelFaderOriginId;
			auto actualChannel = linkedMixerFake->SetInputChannelFaderChannel;
			auto actualValue = linkedMixerFake->SetInputChannelFaderValue;

			if (expectedOrigin == linkedMixerFake->Id)
			{
				EXPECT_FALSE(actualOrigin.has_value());
				EXPECT_FALSE(actualChannel.has_value());
				EXPECT_FALSE(actualValue.has_value());
			}
			else
			{
				EXPECT_EQ(expectedOrigin, actualOrigin);
				EXPECT_EQ(expectedChannel, actualChannel);
				EXPECT_EQ(expectedValue, actualValue);
			}
		}
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::Mixers