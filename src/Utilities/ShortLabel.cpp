//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "ShortLabel.h"

namespace MackieOfTheUnicorn::Utilities
{
	enum class CharacterType {
		VOWEL,
		CONSONANT,
		NUMBER,
		OTHER,
		SKIP
	};

	static constexpr std::string_view Vowels = "aeiouyAEIOUY";
	static constexpr std::string_view Consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
	static constexpr int NUMBERS_0 = 48;
	static constexpr int NUMBERS_9 = 57;

	static void CopyString(const char* input, char* output, size_t size)
	{
		for (int i = 0; i < size; ++i)
		{
			*(output++) = *(input++);
		}
	}

	static std::vector<CharacterType> GetCharacterTypes(std::string_view inputLabel)
	{
		std::vector<CharacterType> characterTypes;
		characterTypes.reserve(inputLabel.size());

		for (const char* inputPtr = inputLabel.data(); *inputPtr != '\0'; ++inputPtr)
		{
			char currentCharacter = *inputPtr;
			if (currentCharacter >= NUMBERS_0 && currentCharacter <= NUMBERS_9)
			{
				characterTypes.push_back(CharacterType::NUMBER);
				continue;
			}

			auto isVowel = std::any_of(Vowels.begin(), Vowels.end(), [&currentCharacter] (auto vowel) { return currentCharacter == vowel; });
			if (isVowel)
			{
				characterTypes.push_back(CharacterType::VOWEL);
				continue;
			}

			auto isConsonant = std::any_of(Consonants.begin(), Consonants.end(), [&currentCharacter] (auto consonant) { return currentCharacter == consonant; });

			if (isConsonant)
			{
				characterTypes.push_back(CharacterType::CONSONANT);
				continue;
			}

			characterTypes.push_back(CharacterType::OTHER);
		}

		return characterTypes;
	}

	static void SkipCharacters(std::vector<CharacterType>& characterTypes, CharacterType character, int& skipped)
	{
		auto it = characterTypes.begin() + (characterTypes.size() / 2);
		for (int i = 0; i < characterTypes.size(); ++i)
		{
			if (characterTypes.size() - skipped <= ShortLabel::MAX_LENGTH || it == characterTypes.begin() || it == characterTypes.end() - 1)
			{
				break;
			}

			if (*it == character)
			{
				*it = CharacterType::SKIP;
				++skipped;
			}

			if (i % 2 == 0)
			{
				it += i + 1;
			}
			else
			{
				it -= i + 1;
			}
		}
	}

	static void CopyStringFiltered(const char* input, char* output, std::vector<CharacterType>& characterTypes)
	{
		auto it = characterTypes.begin();
		for (char* outputPtr = output; *outputPtr != '\0'; ++outputPtr)
		{
			while (*it == CharacterType::SKIP)
			{
				++it;
				++input;
			}

			*outputPtr = *(input++);
			++it;
		}
	}

	ShortLabel::ShortLabel(std::string_view inputLabel) : OutputLabel("      ")
	{
		if (inputLabel.length() <= MAX_LENGTH)
		{
			CopyString(inputLabel.data(), OutputLabel, inputLabel.length());
			return;
		}

		auto characterTypes = GetCharacterTypes(inputLabel);

		int skipped = 0;

		SkipCharacters(characterTypes, CharacterType::VOWEL, skipped);
		SkipCharacters(characterTypes, CharacterType::CONSONANT, skipped);
		SkipCharacters(characterTypes, CharacterType::OTHER, skipped);
		SkipCharacters(characterTypes, CharacterType::NUMBER, skipped);

		CopyStringFiltered(inputLabel.data(), OutputLabel, characterTypes);
	}

	std::string_view ShortLabel::Get()
	{
		return OutputLabel;
	}
}