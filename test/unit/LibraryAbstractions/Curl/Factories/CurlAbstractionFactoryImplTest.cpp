//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "gtest/gtest.h"
#include "../../../../src/LibraryAbstractions/Curl/Factories/CurlAbstractionFactoryImpl.h"

namespace MackieOfTheUnicorn::Tests::Unit::LibraryAbstractions::Curl::Factories
{
	class CurlAbstractionFactoryImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			instance = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryImpl>();
		}

		std::unique_ptr<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryImpl> instance;
	};

	TEST_F(CurlAbstractionFactoryImplTest, CreatesCurlInstance)
	{
		auto curlAbstraction = instance->Create();

		EXPECT_NE(curlAbstraction.get(), nullptr);
	}
}
