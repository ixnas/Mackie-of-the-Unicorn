//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#include "../../../src/Mixers/VirtualMixerBuilder.h"
#include "../../fakes/Mackie/MackieServiceFake.h"
#include "../../../src/Exceptions/DeviceUnavailableException.h"
#include "../../fakes/HTTP/Factories/HTTPDeviceFactoryFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mixers
{
	class VirtualMixerBuilderTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieServiceFake = std::make_unique<Mackie::MackieServiceFake>();
			httpDeviceFactoryFake = std::make_unique<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactoryFake>();
			instance = std::make_unique<MackieOfTheUnicorn::Mixers::VirtualMixerBuilder>(*mackieServiceFake, *httpDeviceFactoryFake);
		}

		std::unique_ptr<MackieOfTheUnicorn::Mackie::MackieServiceFake> mackieServiceFake;
		std::unique_ptr<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactoryFake> httpDeviceFactoryFake;
		std::unique_ptr<MackieOfTheUnicorn::Mixers::VirtualMixerBuilder> instance;
	};

	TEST_F(VirtualMixerBuilderTest, MethodsReturnInstance)
	{
		mackieServiceFake->InputDevices = {{0, "input1"}};
		mackieServiceFake->OutputDevices = {{0, "output1"}};

		std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
		auto expectedInstance = instance.get();
		auto actualInstance = instance->AddMackieMixer(inputAndOutputIds);

		EXPECT_EQ(actualInstance, expectedInstance);
	}

	TEST_F(VirtualMixerBuilderTest, InvalidDeviceThrowsException)
	{
		std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};

		EXPECT_THROW({
		    instance->AddMackieMixer(inputAndOutputIds);
		}, Exceptions::DeviceUnavailableException);
	}

	TEST_F(VirtualMixerBuilderTest, CreatesVirtualMixer)
	{
		mackieServiceFake->InputDevices = {{0, "input1"}};
		mackieServiceFake->OutputDevices = {{0, "output1"}};

		std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
		instance->AddMackieMixer(inputAndOutputIds);
		instance->AddMOTUMixer("motu.local");
		auto actualInstance = instance->Build();

		EXPECT_NE(actualInstance.get(), nullptr);
	}

	TEST_F(VirtualMixerBuilderTest, BuildThrowsExceptionIfNoMackieMixer)
	{
		instance->AddMOTUMixer("motu.local");
		EXPECT_THROW({
			instance->Build();
		}, Exceptions::DeviceUnavailableException);
	}

	TEST_F(VirtualMixerBuilderTest, BuildThrowsExceptionIfNoMOTUMixer)
	{
		mackieServiceFake->InputDevices = {{0, "input1"}};
		mackieServiceFake->OutputDevices = {{0, "output1"}};

		std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
		instance->AddMackieMixer(inputAndOutputIds);
		EXPECT_THROW({
						 instance->Build();
					 }, Exceptions::DeviceUnavailableException);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::Mixers