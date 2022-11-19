//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "gtest/gtest.h"
#include "../../../src/Utilities/FaderValueConverter.h"

namespace MackieOfTheUnicorn::Tests::Unit::Utilities
{
	using namespace MackieOfTheUnicorn::Utilities;
	TEST(FaderValueConverterTest, ConvertsMaxValueToMotu)
	{
		double expected = 4.0;
		double input = 1.0;

		auto actual = FaderValueConverter::ToMotu(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, ConvertsMaxValueToLinear)
	{
		double expected = 1.0;
		double input = 4.0;

		auto actual = FaderValueConverter::ToLinear(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, ConvertsHalfValueToQuarterMotu)
	{
		double expected = 0.25;
		double input = 0.5;

		auto actual = FaderValueConverter::ToMotu(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, ConvertsQuarterValueToHalfLinear)
	{
		double expected = 0.5;
		double input = 0.25;

		auto actual = FaderValueConverter::ToLinear(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, ConvertsZeroToZero)
	{
		int expected = 0;
		double input = 0;

		auto actual = FaderValueConverter::To10bitInteger(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, ConvertsOneTo1023)
	{
		int expected = 1024;
		double input = 1;

		auto actual = FaderValueConverter::To10bitInteger(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, ConvertsZeroToZeroZero)
	{
		std::array<unsigned char, 2> expected = {0x00, 0x00};
		int input = 0;

		auto actual = FaderValueConverter::ToSplit10BitInteger(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Converts1023To7F7F)
	{
		std::array<unsigned char, 2> expected = {0x7F, 0x7F};
		int input = 1023;

		auto actual = FaderValueConverter::ToSplit10BitInteger(input);

		EXPECT_EQ(actual, expected);
	}

	TEST(FaderValueConverterTest, Converts192Tox40x18)
	{
		std::array<unsigned char, 2> expected = {0x40, 0x18};
		int input = 192;

		auto actual = FaderValueConverter::ToSplit10BitInteger(input);

		EXPECT_EQ(actual, expected);
	}
}