//
// Created by Sjoerd Scheffer on 06/02/2022.
//
#include "../../src/Application.h"
#include "../fakes/Mackie/MackieServiceFake.h"
#include "gtest/gtest.h"
#include "../fakes/HTTP/Factories/HTTPDeviceFactoryFake.h"

namespace MackieOfTheUnicorn::Tests::Integration
{
	class ApplicationTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieService = std::make_unique<Mackie::MackieServiceFake>();
			httpDeviceFactoryFake = std::make_unique<HTTP::Factories::HTTPDeviceFactoryFake>();
			virtualMixerBuilder = std::make_unique<MackieOfTheUnicorn::Mixers::VirtualMixerBuilder>(*mackieService, *httpDeviceFactoryFake);
			instance = std::make_unique<MackieOfTheUnicorn::Application>(*mackieService, *virtualMixerBuilder);
		}

		std::unique_ptr<Mixers::VirtualMixerBuilder> virtualMixerBuilder;
		std::unique_ptr<HTTP::Factories::HTTPDeviceFactoryFake> httpDeviceFactoryFake;
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
} // namespace MackieOfTheUnicorn::Tests::Integration
