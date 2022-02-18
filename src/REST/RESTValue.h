//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RESTVALUE_H
#define MACKIE_OF_THE_UNICORN_RESTVALUE_H

#include <optional>
#include <string>

namespace MackieOfTheUnicorn::REST
{
	/// A value container for REST values.
	struct RESTValue
	{
		std::optional<int> Integer;
		std::optional<std::string> String;
		std::optional<float> Float;
	};
}

#endif // MACKIE_OF_THE_UNICORN_RESTVALUE_H
