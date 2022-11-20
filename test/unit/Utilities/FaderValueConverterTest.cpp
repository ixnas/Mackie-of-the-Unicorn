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
		std::array<unsigned char, 2> expected = {0x40, 0x18};
		int input = 192;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMid)
	{
		std::array<unsigned char, 2> expected = {0x00, 0x40};
		int input = 512;

		auto actual = FaderValueConverter::Integer10bitToMackie(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Integer10bitToMackieConvertsMidHigh)
	{
		std::array<unsigned char, 2> expected = {0x40, 0x68};
		int input = 832;

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
		int expected = 192;
		std::array<unsigned char, 2> input = {0x40, 0x18};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMid)
	{
		int expected = 512;
		std::array<unsigned char, 2> input = {0x00, 0x40};

		auto actual = FaderValueConverter::MackieToInteger10bit(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, MackieToInteger10bitConvertsMidHigh)
	{
		int expected = 832;
		std::array<unsigned char, 2> input = {0x40, 0x68};

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