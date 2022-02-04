//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "../../src/Application.h"
#include "../../src/Mackie/MackieComposite.h"
#include "../../src/Mackie/MackieService.h"
#include "gtest/gtest.h"
#include "../fakes/Mackie/MackieServiceFake.h"

namespace MackieOfTheUnicorn
{
	class ApplicationTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieService = std::make_unique<Mackie::MackieServiceFake>();
			instance = std::make_unique<MackieOfTheUnicorn::Application>(*mackieService);
		}

		std::unique_ptr<Mackie::MackieServiceFake> mackieService;
		std::unique_ptr<MackieOfTheUnicorn::Application> instance;
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
}
