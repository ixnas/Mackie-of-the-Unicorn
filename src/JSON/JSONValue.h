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
		std::optional<int> Integer;
		std::optional<std::string> String;
		std::optional<float> Float;

		bool operator==(JSONValue const& object) const;
	};
} // namespace MackieOfTheUnicorn::JSON

#endif // MACKIE_OF_THE_UNICORN_JSONVALUE_H
