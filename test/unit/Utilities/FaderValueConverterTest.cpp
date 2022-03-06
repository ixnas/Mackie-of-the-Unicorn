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
}