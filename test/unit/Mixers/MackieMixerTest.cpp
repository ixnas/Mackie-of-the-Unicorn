//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "gtest/gtest.h"
#include "../../../src/Mixers/MackieMixer.h"
#include "../../fakes/Mackie/MackieCompositeFake.h"
#include "../../fakes/Mixers/VirtualMixerFake.h"
#include <memory>

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

		instance->OnSetChannelMute(mackieCompositeFake, expectedChannel, expectedOn);

		auto actualOriginId = virtualMixerFake->SetInputChannelMuteOriginId = expectedOriginId;
		auto actualChannel = virtualMixerFake->SetInputChannelMuteChannel;
		auto actualOn = virtualMixerFake->SetInputChannelMuteOn;

		EXPECT_EQ(actualOriginId, expectedOriginId);
		EXPECT_EQ(actualChannel, expectedChannel);
		EXPECT_EQ(actualOn, expectedOn);
	}
}