//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "gtest/gtest.h"
#include "../../../../src/HTTP/Factories/HTTPDeviceFactoryImpl.h"
#include "../../../fakes/LibraryAbstractions/Curl/Factories/CurlAbstractionFactoryFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::HTTP::Factories
{
	class HTTPDeviceFactoryImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			curlAbstractionFactoryFake = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryFake>();
			instance = std::make_unique<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactoryImpl>(*curlAbstractionFactoryFake);
		}

		std::unique_ptr<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryFake> curlAbstractionFactoryFake;
		std::unique_ptr<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactoryImpl> instance;
	};

	TEST_F(HTTPDeviceFactoryImplTest, CreatesHTTPDevice)
	{
		auto expectedUrl = "http://motu.local/datastore";
		auto httpDevice = instance->Create(expectedUrl);

		auto curlInstances = curlAbstractionFactoryFake->CreateCurlAbstractionFakes;
		auto hasCurlInstances = !curlAbstractionFactoryFake->CreateCurlAbstractionFakes.empty();

		EXPECT_TRUE(hasCurlInstances);

		for (const auto curlInstance: curlInstances)
		{
			auto actualUrl = curlInstance->SetURLURL;
			EXPECT_EQ(actualUrl, expectedUrl);
		}

		EXPECT_NE(httpDevice.get(), nullptr);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::HTTP
