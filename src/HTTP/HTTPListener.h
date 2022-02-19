//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPLISTENER_H
#define MACKIE_OF_THE_UNICORN_HTTPLISTENER_H

#include "../JSON/JSONValue.h"
#include <vector>
#include <string>

namespace MackieOfTheUnicorn::HTTP
{
	/// Interface for classes that implement a callback to receive JSON HTTP messages as key/value pairs.
	class HTTPListener
	{
	  public:
		virtual ~HTTPListener() = default;

		/// The callback function that will be called with the JSON message as a parameter.
		virtual void HTTPCallback(std::pair<std::string, JSON::JSONValue>& message) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPLISTENER_H
