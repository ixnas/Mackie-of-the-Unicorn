//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#include "gtest/gtest.h"
#include "../../../src/HTTP/ETagParser.h"

namespace MackieOfTheUnicorn::Tests::Unit::HTTP
{
	class ETagParserTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			instance = std::make_unique<MackieOfTheUnicorn::HTTP::ETagParser>();
		}

		std::unique_ptr<MackieOfTheUnicorn::HTTP::ETagParser> instance;
	};

	TEST_F(ETagParserTest, ReturnsETagIfAvailable)
	{
		auto expected = 6664;
		auto headers = "HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nTransfer-Encoding: chunked\r\nETag: 6664\r\nContent-Type: application/json\r\nCache-Control: no-cache\r\nAccess-Control-Expose-Headers: Content-Type,ETag\r\nAccess-Control-Allow-Origin: *\r\nDate: Thu, 01 Jan 1970 05:50:33 GMT\r\n\r\n";

		auto actual = instance->GetETag(headers);

		EXPECT_TRUE(actual.has_value());
		EXPECT_EQ(actual.value(), expected);
	}

	TEST_F(ETagParserTest, ReturnsEmptyIfNotAvailable)
	{
		auto headers = "HTTP/1.1 304 Not Modified\r\nConnection: Keep-Alive\r\nContent-Length: 0\r\nCache-Control: no-cache\r\nAccess-Control-Allow-Origin: *\r\nDate: Thu, 01 Jan 1970 05:54:06 GMT\r\n\r\n";
		auto actual = instance->GetETag(headers);

		EXPECT_FALSE(actual.has_value());
	}
}