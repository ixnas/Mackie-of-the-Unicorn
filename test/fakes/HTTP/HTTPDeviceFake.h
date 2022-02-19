//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPDEVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_HTTPDEVICEFAKE_H

#include "../../../src/HTTP/HTTPDevice.h"
#include "../../../src/HTTP/HTTPListener.h"

namespace MackieOfTheUnicorn::HTTP
{
	class HTTPDeviceFake : public HTTPDevice
	{
	  public:
		std::optional<bool> IsListening;
		HTTPListener* RegisterCallbackListener = nullptr;
		std::vector<std::pair<std::string, JSON::JSONValue>> SendMessageMessages;

		void StartListening() override
		{
			IsListening = true;
		}

		void StopListening() override
		{
			IsListening = false;
		}

		void RegisterCallback(HTTPListener& listener) override
		{
			RegisterCallbackListener = &listener;
		}

		void SendMessage(std::pair<std::string, JSON::JSONValue>& message) override
		{
			SendMessageMessages.push_back(message);
		}

		void FakeMessage(std::pair<std::string, JSON::JSONValue>& message) const
		{
			RegisterCallbackListener->HTTPCallback(message);
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPDEVICEFAKE_H
