//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "HTTPDeviceFactoryImpl.h"
#include "../HTTPDeviceImpl.h"

namespace MackieOfTheUnicorn::HTTP::Factories
{
	HTTPDeviceFactoryImpl::HTTPDeviceFactoryImpl(
	    LibraryAbstractions::Curl::Factories::CurlAbstractionFactory& curlAbstractionFactory)
	    : CurlAbstractionFactory(&curlAbstractionFactory)
	{
	}

	std::unique_ptr<HTTPDevice> HTTPDeviceFactoryImpl::Create(std::string url)
	{
		auto curlIn = CurlAbstractionFactory->Create();
		auto curlOut = CurlAbstractionFactory->Create();

		curlIn->SetURL(url);
		curlOut->SetURL(url);

		return std::make_unique<HTTPDeviceImpl>(std::move(curlIn), std::move(curlOut));
	}
} // namespace MackieOfTheUnicorn::HTTP::Factories
