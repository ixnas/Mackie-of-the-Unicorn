//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_JSONVALUE_H
#define MACKIE_OF_THE_UNICORN_JSONVALUE_H

#include <optional>
#include <string>

namespace MackieOfTheUnicorn::JSON
{
	/// A value container for JSON values.
	struct JSONValue
	{
		/// Integer representation if it's present.
		std::optional<int> Integer;

		/// String representation if it's present.
		std::optional<std::string> String;

		/// Float representation if it's present.
		std::optional<float> Float;

		/// Enables comparing all values between two JSONValue objects.
		bool operator==(JSONValue const& object) const;
	};
} // namespace MackieOfTheUnicorn::JSON

#endif // MACKIE_OF_THE_UNICORN_JSONVALUE_H
