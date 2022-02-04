//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "../../../src/Mackie/MackieServiceImpl.h"
#include "../../../src/MIDI/MIDIDevice.h"
#include "../../../src/MIDI/MIDIService.h"
#include "../../../src/Mackie/MackieComposite.h"
#include "../../../src/Mackie/Factories/MackieCompositeFactory.h"
#include "../../../src/Mackie/MackieDevice.h"
#include "../../../src/Mackie/Factories/MackieDeviceFactory.h"
#include "gtest/gtest.h"
#include "../../fakes/Mackie/MackieCompositeFake.h"
#include "../../fakes/Mackie/Factories/MackieCompositeFactoryFake.h"
#include "../../fakes/Mackie/Factories/MackieDeviceFactoryFake.h"
#include "../../fakes/MIDI/MIDIServiceFake.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieServiceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieDeviceFactory = std::make_unique<Factories::MackieDeviceFactoryFake>();
			mackieCompositeFactory = std::make_unique<Factories::MackieCompositeFactoryFake>();
			midiService = std::make_unique<MIDI::MIDIServiceFake>();
			instance = std::make_unique<MackieServiceImpl>(*mackieCompositeFactory, *mackieDeviceFactory, *midiService);
		}

		std::unique_ptr<MackieServiceImpl> instance;
		std::unique_ptr<Factories::MackieDeviceFactoryFake> mackieDeviceFactory;
		std::unique_ptr<Factories::MackieCompositeFactoryFake> mackieCompositeFactory;
		std::unique_ptr<MIDI::MIDIServiceFake> midiService;
	};

	TEST_F(MackieServiceImplTest, GetsDevicesListFromMIDIService)
	{
		auto expectedInputs = midiService->GetInputDevices();
		auto expectedOutputs = midiService->GetOutputDevices();

		auto actualInputs = instance->GetInputDevices();
		auto actualOutputs = instance->GetOutputDevices();

		EXPECT_EQ(expectedInputs, actualInputs);
		EXPECT_EQ(expectedOutputs, actualOutputs);
	}

	TEST_F(MackieServiceImplTest, CreatesCompositeWithSingleDevice)
	{
		std::vector<std::pair<int, int>> input = {{5, 6}};

		auto actual = instance->GetMackieComposite(input);
		auto actualPtr = (MackieCompositeFake*)actual.get();

		EXPECT_EQ(input.size(), actualPtr->Devices.size());
	}

	TEST_F(MackieServiceImplTest, CreatesCompositeWithMultipleDevices)
	{
		std::vector<std::pair<int, int>> input = {{5, 6}, {8, 9}};

		auto actual = instance->GetMackieComposite(input);
		auto actualPtr = (MackieCompositeFake*)actual.get();

		EXPECT_EQ(input.size(), actualPtr->Devices.size());
	}
}
