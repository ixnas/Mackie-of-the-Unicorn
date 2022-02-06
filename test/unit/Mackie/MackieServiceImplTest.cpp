//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "../../../src/Mackie/MackieServiceImpl.h"
#include "../../../src/MIDI/MIDIDevice.h"
#include "../../../src/MIDI/MIDIService.h"
#include "../../../src/Mackie/Factories/MackieCompositeFactory.h"
#include "../../../src/Mackie/MackieComposite.h"
#include "../../../src/Mackie/MackieDevice.h"
#include "../../fakes/MIDI/MIDIServiceFake.h"
#include "../../fakes/Mackie/Factories/MackieCompositeFactoryFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mackie
{
	using namespace MackieOfTheUnicorn::Mackie;

	class MackieServiceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieCompositeFactory = std::make_unique<Factories::MackieCompositeFactoryFake>();
			midiService = std::make_unique<MIDI::MIDIServiceFake>();
			instance = std::make_unique<MackieServiceImpl>(*mackieCompositeFactory, *midiService);
		}

		std::unique_ptr<MackieServiceImpl> instance;
		std::unique_ptr<Factories::MackieCompositeFactoryFake> mackieCompositeFactory;
		std::unique_ptr<MIDI::MIDIServiceFake> midiService;
	};

	TEST_F(MackieServiceImplTest, ReturnsDevicesList)
	{
		auto actualInputs = instance->GetInputDevices();
		auto actualOutputs = instance->GetOutputDevices();
	}

	TEST_F(MackieServiceImplTest, ReturnsComposite)
	{
		std::vector<std::pair<int, int>> input = {{5, 6}};

		auto actual = instance->GetMackieComposite(input);
		auto actualPtr = (MackieCompositeFake*)actual.get();

		EXPECT_NE(nullptr, actualPtr);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie
