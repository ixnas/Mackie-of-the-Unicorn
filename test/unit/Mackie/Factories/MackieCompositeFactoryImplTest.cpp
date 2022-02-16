//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#include "gtest/gtest.h"
#include "../../../../src/Mackie/Factories/MackieCompositeFactoryImpl.h"
#include "../../../fakes/MIDI/MIDIServiceFake.h"
#include "../../../fakes/Mackie/Factories/MackieDeviceFactoryFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mackie::Factories
{
	class MackieCompositeFactoryImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieDeviceFactoryFake = std::make_unique<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryFake>();
			midiServiceFake = std::make_unique<MIDI::MIDIServiceFake>();
			instance = std::make_unique<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactoryImpl>(*midiServiceFake, *mackieDeviceFactoryFake);
		}

		std::unique_ptr<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactory> mackieDeviceFactoryFake;
		std::unique_ptr<MackieOfTheUnicorn::MIDI::MIDIServiceFake> midiServiceFake;
		std::unique_ptr<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactoryImpl> instance;
	};

	TEST_F(MackieCompositeFactoryImplTest, ReturnsProperComposite)
	{
		std::vector<std::pair<int, int>> input = {{0, 0}};
		auto actualComposite = instance->Create(input);

		EXPECT_NE(actualComposite.get(), nullptr);
	}
}
