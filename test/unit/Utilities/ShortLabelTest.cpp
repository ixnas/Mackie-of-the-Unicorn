//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "gtest/gtest.h"
#include "../../../src/Utilities/ShortLabel.h"

namespace MackieOfTheUnicorn::Tests::Unit::Utilities
{
	using namespace MackieOfTheUnicorn::Utilities;

	TEST(ShortLabelTest, LabelShorterThan7)
	{
		std::string input = "abc";

		ShortLabel shortLabel(input);

		auto expected = "abc   ";
		auto actual = shortLabel.Get();

		EXPECT_EQ(actual, expected);
	}

	TEST(ShortLabelTest, LabelLongerThan7)
	{
		std::string input = "abcdefgh";
		ShortLabel shortLabel(input);

		auto expectedLength = 6;
		auto actualLength = shortLabel.Get().length();

		EXPECT_EQ(actualLength, expectedLength);
	}

	TEST(ShortLabelTest, LongLableRetainsBeginAndEnd)
	{
		std::string input = "abcdefgh";
		ShortLabel shortLabel(input);

		auto outputLabel = shortLabel.Get();

		auto expectedBegin = 'a';
		auto actualBegin = outputLabel[0];

		auto expectedEnd = 'h';
		auto actualEnd = outputLabel[5];

		EXPECT_EQ(actualBegin, expectedBegin);
		EXPECT_EQ(actualEnd, expectedEnd);
	}

	TEST(ShortLabelTest, RemovesMiddleVowelsFirst)
	{
		std::string input = "abciefgh";
		ShortLabel shortLabel(input);

		auto expected = "abcfgh";
		auto actual = shortLabel.Get();

		EXPECT_EQ(actual, expected);
	}

	TEST(ShortLabelTest, RemovesConsonants)
	{
		std::string input = "abddciefwhhwwgh";
		ShortLabel shortLabel(input);

		auto expected = "abdwgh";
		auto actual = shortLabel.Get();

		EXPECT_EQ(actual, expected);
	}

	TEST(ShortLabelTest, RemovesNumbers)
	{
		std::string input = "a987382347gh";
		ShortLabel shortLabel(input);

		auto expected = "a9877h";
		auto actual = shortLabel.Get();

		EXPECT_EQ(actual, expected);
	}

	TEST(ShortLabelTest, RemovesOtherCharacters)
	{
		std::string input = "a.,/.>,.||'gh";
		ShortLabel shortLabel(input);

		auto expected = "a.,/'h";
		auto actual = shortLabel.Get();

		EXPECT_EQ(actual, expected);
	}
}
