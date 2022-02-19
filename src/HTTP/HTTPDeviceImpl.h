//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPDEVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_HTTPDEVICEIMPL_H

#include "HTTPDevice.h"
#include "../LibraryAbstractions/Curl/CurlAbstraction.h"
#include <future>

namespace MackieOfTheUnicorn::HTTP
{
	class HTTPDeviceImpl : public HTTPDevice
	{
		HTTPListener* Listener;
		LibraryAbstractions::Curl::CurlAbstraction* CurlIn;
		LibraryAbstractions::Curl::CurlAbstraction* CurlOut;
		bool Running;
		std::future<void> Task;

		void Loop();

	  public:
		explicit HTTPDeviceImpl(LibraryAbstractions::Curl::CurlAbstraction& curlIn,
								LibraryAbstractions::Curl::CurlAbstraction& curlOut);
		~HTTPDeviceImpl() override;
		void StartListening() override;
		void StopListening() override;
		void RegisterCallback(HTTPListener& listener) override;
		void SendMessage(std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>& message) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPDEVICEIMPL_H
