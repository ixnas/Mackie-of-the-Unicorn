//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPDEVICE_H
#define MACKIE_OF_THE_UNICORN_HTTPDEVICE_H
#include <vector>
#include <string>
#include "../JSON/JSONValue.h"

namespace MackieOfTheUnicorn::HTTP
{
	class HTTPListener;

	/// Provides an interface to communicate with a connected HTTP device.
	class HTTPDevice
	{
	  public:
		virtual ~HTTPDevice() = default;

		/// Starts listening to messages from the HTTP device.
		virtual void StartListening() = 0;

		/// Stops listening to messages from the HTTP device.
		virtual void StopListening() = 0;

		/// Sets a callback function for whenever the HTTP device sends a message to the application.
		virtual void RegisterCallback(HTTPListener& listener) = 0;

		/// Sends a JSON message to the HTTP device.
		virtual void SendMessage(std::pair<std::string, JSON::JSONValue>& message) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPDEVICE_H
