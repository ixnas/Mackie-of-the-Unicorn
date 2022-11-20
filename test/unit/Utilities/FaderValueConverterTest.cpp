//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "gtest/gtest.h"
#include "../../../src/Utilities/FaderValueConverter.h"

namespace MackieOfTheUnicorn::Tests::Unit::Utilities
{
	using namespace MackieOfTheUnicorn::Utilities;
	TEST(FaderValueConverterTest, LinearToMotuConvertsMaxValueToMotu)
	{
		double expected = 4.0;
		double input = 1.0;

		auto actual = FaderValueConverter::LinearToMotu(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MotuToLinearConvertsMaxValueToLinear)
	{
		double expected = 1.0;
		double input = 4.0;

		auto actual = FaderValueConverter::MotuToLinear(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, LinearToMotuConvertsHalfValueToQuarterMotu)
	{
		double expected = 0.25;
		double input = 0.5;

		auto actual = FaderValueConverter::LinearToMotu(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MotuToLinearConvertsQuarterValueToHalfLinear)
	{
		double expected = 0.5;
		double input = 0.25;

		auto actual = FaderValueConverter::MotuToLinear(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, LinearToInteger10bitConvertsMin)
	{
		int expected = 0;
		double input = 0;

		auto actual = FaderValueConverter::LinearToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, LinearToInteger10bitConvertsMid)
	{
		int expected = 511;
		double input = 0.5;

		auto actual = FaderValueConverter::LinearToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, LinearToInteger10bitConvertsMax)
	{
		int expected = 1023;
		double input = 1;

		auto actual = FaderValueConverter::LinearToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToLinearConvertsMin)
	{
		double expected = 0;
		int input = 0;

		auto actual = FaderValueConverter::Integer10bitToLinear(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToLinearConvertsMax)
	{
		double expected = 1;
		int input = 1023;

		auto actual = FaderValueConverter::Integer10bitToLinear(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMin)
	{
		std::array<unsigned char, 2> expected = {0x00, 0x00};
		int input = 0;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMax)
	{
		std::array<unsigned char, 2> expected = {0x7F, 0x7F};
		int input = 1023;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMidLow)
	{
		std::array<unsigned char, 2> expected = {0x3F, 0x17};
		int input = 191;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMid)
	{
		std::array<unsigned char, 2> expected = {0x7F, 0x3F};
		int input = 511;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMidHigh)
	{
		std::array<unsigned char, 2> expected = {0x3F, 0x67};
		int input = 831;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMin)
	{
		int expected = 0;
		std::array<unsigned char, 2> input = {0x00, 0x00};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMidLow)
	{
		int expected = 191;
		std::array<unsigned char, 2> input = {0x3F, 0x17};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMid)
	{
		int expected = 511;
		std::array<unsigned char, 2> input = {0x7F, 0x3F};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMidHigh)
	{
		int expected = 831;
		std::array<unsigned char, 2> input = {0x3F, 0x67};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMax)
	{
		int expected = 1023;
		std::array<unsigned char, 2> input = {0x7F, 0x7F};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}
}