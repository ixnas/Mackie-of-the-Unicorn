//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPLISTENERFAKE_H
#define MACKIE_OF_THE_UNICORN_HTTPLISTENERFAKE_H

#include "../../../src/HTTP/HTTPListener.h"

namespace MackieOfTheUnicorn::HTTP
{
	class HTTPListenerFake : public HTTPListener
	{
	  public:
		std::vector<std::pair<std::string, JSON::JSONValue>> Messages;

		void HTTPCallback(std::pair<std::string, JSON::JSONValue>& message) override
		{
			Messages.push_back(message);
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPLISTENERFAKE_H
