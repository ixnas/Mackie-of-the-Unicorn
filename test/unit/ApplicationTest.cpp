//
// Created by Sjoerd Scheffer on 06/02/2022.
//
#include "../../src/Application.h"
#include "../fakes/Mackie/MackieServiceFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Integration
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

	TEST_F(ApplicationTest, GetAvailableInputDevicesReturnsList)
	{
		auto actual = instance->GetAvailableInputDevices();
	}

	TEST_F(ApplicationTest, GetAvailableOutputDevicesReturnsList)
	{
		auto actual = instance->GetAvailableOutputDevices();
	}
} // namespace MackieOfTheUnicorn::Tests::Integration
