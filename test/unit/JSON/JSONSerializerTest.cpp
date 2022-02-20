//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#include "gtest/gtest.h"
#include "../../../src/JSON/JSONSerializer.h"
#include "../../../src/JSON/JSONValue.h"

namespace MackieOfTheUnicorn::Tests::Unit::JSON
{
	class JSONSerializerTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			instance = std::make_unique<MackieOfTheUnicorn::JSON::JSONSerializer>();
		}

		std::unique_ptr<MackieOfTheUnicorn::JSON::JSONSerializer> instance;
	};

	TEST_F(JSONSerializerTest, ParsesStringsCorrectly)
	{
		auto expectedKey = "someKey";
		MackieOfTheUnicorn::JSON::JSONValue expectedValue;
		expectedValue.String = "someValue";

		std::ostringstream inputStringStream;
		inputStringStream << "{\"" << expectedKey << "\":\"" << expectedValue.String.value() << "\"}";
		auto input = inputStringStream.str();

		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> expectedObject = {{expectedKey, expectedValue}};

		auto actualObject = instance->Parse(input);

		EXPECT_EQ(actualObject, expectedObject);
	}

	TEST_F(JSONSerializerTest, ParsesIntegersCorrectly)
	{
		auto expectedKey = "someKey";
		MackieOfTheUnicorn::JSON::JSONValue expectedValue;
		expectedValue.Integer = 128;

		std::ostringstream inputStringStream;
		inputStringStream << "{\"" << expectedKey << "\":" << expectedValue.Integer.value() << "}";
		auto input = inputStringStream.str();

		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> expectedObject = {{expectedKey, expectedValue}};

		auto actualObject = instance->Parse(input);

		EXPECT_EQ(actualObject, expectedObject);
	}

	TEST_F(JSONSerializerTest, ParsesFloatsCorrectly)
	{
		auto expectedKey = "someKey";
		MackieOfTheUnicorn::JSON::JSONValue expectedValue;
		expectedValue.Float = 1.004;

		std::ostringstream inputStringStream;
		inputStringStream << "{\"" << expectedKey << "\":" << expectedValue.Float.value() << "}";
		auto input = inputStringStream.str();

		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> expectedObject = {{expectedKey, expectedValue}};

		auto actualObject = instance->Parse(input);

		EXPECT_EQ(actualObject, expectedObject);
	}

	TEST_F(JSONSerializerTest, ParsesMultipleEntriesCorrectly)
	{
		auto expectedLength = 3;
		std::string input = "{\"key1\":\"string\",\"key2\":1,\"key3\":1.004}";

		auto actualLength = instance->Parse(input).size();

		EXPECT_EQ(actualLength, expectedLength);
	}

	TEST_F(JSONSerializerTest, SerializesStringsCorrectly)
	{
		std::string inputKey = "someKey";
		MackieOfTheUnicorn::JSON::JSONValue inputValue;
		inputValue.String = "someValue";
		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> input = {{inputKey, inputValue}};

		std::string expectedString = "{\"someKey\":\"someValue\"}";

		auto actualString = instance->Serialize(input);

		EXPECT_EQ(actualString, expectedString);
	}

	TEST_F(JSONSerializerTest, SerializesIntegersCorrectly)
	{
		std::string inputKey = "someKey";
		MackieOfTheUnicorn::JSON::JSONValue inputValue;
		inputValue.Integer = 128;
		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> input = {{inputKey, inputValue}};

		std::string expectedString = "{\"someKey\":128}";

		auto actualString = instance->Serialize(input);

		EXPECT_EQ(actualString, expectedString);
	}

	TEST_F(JSONSerializerTest, SerializesFloatsCorrectly)
	{
		std::string inputKey = "someKey";
		MackieOfTheUnicorn::JSON::JSONValue inputValue;
		inputValue.Float = 1.5;
		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> input = {{inputKey, inputValue}};

		std::string expectedString = "{\"someKey\":1.5}";

		auto actualString = instance->Serialize(input);

		EXPECT_EQ(actualString, expectedString);
	}

	TEST_F(JSONSerializerTest, SerializesMultipleEntriesCorrectly)
	{
		std::string inputKey1 = "key1";
		MackieOfTheUnicorn::JSON::JSONValue inputValue1;
		inputValue1.Integer = 128;

		std::string inputKey2 = "key2";
		MackieOfTheUnicorn::JSON::JSONValue inputValue2;
		inputValue2.Float = 1.5;

		std::string inputKey3 = "key3";
		MackieOfTheUnicorn::JSON::JSONValue inputValue3;
		inputValue3.String = "value";

		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> input =
		{ {inputKey1, inputValue1}, {inputKey2, inputValue2}, {inputKey3, inputValue3} };

		std::string expectedString = "{\"key1\":128,\"key2\":1.5,\"key3\":\"value\"}";

		auto actualString = instance->Serialize(input);

		EXPECT_EQ(actualString, expectedString);
	}

	TEST_F(JSONSerializerTest, EmptyStringReturnsEmptyObject)
	{
		std::string input;
		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> expectedOutput;
		auto actualOutput = instance->Parse(input);
		EXPECT_EQ(actualOutput, expectedOutput);
	}
}