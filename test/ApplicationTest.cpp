//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "../src/Application.h"
#include "../src/MackieComposite.h"
#include "../src/MackieService.h"
#include "gtest/gtest.h"
#include "MackieServiceFake.h"

class ApplicationTest : public ::testing::Test
{
  protected:
	void SetUp() override
	{
		mackieService = std::make_unique<MackieServiceFake>();
		instance = std::make_unique<Application>(*mackieService);
	}

	std::unique_ptr<MackieServiceFake> mackieService;
	std::unique_ptr<Application> instance;
};

TEST_F(ApplicationTest, GetAvailableInputDevicesReturnsProperList)
{
	auto expected = mackieService->GetInputDevices();
	auto actual = instance->GetAvailableInputDevices();

	EXPECT_EQ(expected, actual);
}

TEST_F(ApplicationTest, GetAvailableOutputDevicesReturnsProperList)
{
	auto expected = mackieService->GetOutputDevices();
	auto actual = instance->GetAvailableOutputDevices();

	EXPECT_EQ(expected, actual);
}
