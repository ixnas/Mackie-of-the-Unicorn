//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "../src/MackieServiceImpl.h"
#include "../src/MIDIDevice.h"
#include "../src/MIDIService.h"
#include "../src/MackieComposite.h"
#include "../src/MackieCompositeFactory.h"
#include "../src/MackieDevice.h"
#include "../src/MackieDeviceFactory.h"
#include "gtest/gtest.h"
#include "MackieCompositeFake.h"
#include "MackieCompositeFactoryFake.h"
#include "MackieDeviceFactoryFake.h"
#include "MIDIServiceFake.h"

class MackieServiceImplTest : public ::testing::Test
{
  protected:
	void SetUp() override
	{
		mackieDeviceFactory = std::make_unique<MackieDeviceFactoryFake>();
		mackieCompositeFactory = std::make_unique<MackieCompositeFactoryFake>();
		midiService = std::make_unique<MIDIServiceFake>();
		instance = std::make_unique<MackieServiceImpl>(*mackieCompositeFactory, *mackieDeviceFactory, *midiService);
	}

	std::unique_ptr<MackieServiceImpl> instance;
	std::unique_ptr<MackieDeviceFactoryFake> mackieDeviceFactory;
	std::unique_ptr<MackieCompositeFactoryFake> mackieCompositeFactory;
	std::unique_ptr<MIDIServiceFake> midiService;
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
	auto actualPtr = (MackieCompositeFake*) actual.get();

	EXPECT_EQ(input.size(), actualPtr->Devices.size());
}

TEST_F(MackieServiceImplTest, CreatesCompositeWithMultipleDevices)
{
	std::vector<std::pair<int, int>> input = {{5, 6}, {8, 9}};

	auto actual = instance->GetMackieComposite(input);
	auto actualPtr = (MackieCompositeFake*) actual.get();

	EXPECT_EQ(input.size(), actualPtr->Devices.size());
}

