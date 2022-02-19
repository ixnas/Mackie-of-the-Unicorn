//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORYIMPL_H
#define MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORYIMPL_H

#include "../../LibraryAbstractions/Curl/Factories/CurlAbstractionFactory.h"
#include "HTTPDeviceFactory.h"

namespace MackieOfTheUnicorn::HTTP::Factories
{
	class HTTPDeviceFactoryImpl : public HTTPDeviceFactory
	{
		LibraryAbstractions::Curl::Factories::CurlAbstractionFactory* CurlAbstractionFactory;

	  public:
		explicit HTTPDeviceFactoryImpl(LibraryAbstractions::Curl::Factories::CurlAbstractionFactory& curlAbstractionFactory);
		std::unique_ptr<HTTPDevice> Create(std::string url) override;
	};
} // namespace MackieOfTheUnicorn::HTTP::Factories

#endif // MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORYIMPL_H
