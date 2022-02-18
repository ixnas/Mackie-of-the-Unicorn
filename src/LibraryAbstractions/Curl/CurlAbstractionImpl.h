//
// Created by Sjoerd Scheffer on 17/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTIONIMPL_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTIONIMPL_H

#include "CurlAbstraction.h"
#include <curl/curl.h>
#include <mutex>

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl
{
	class CurlAbstractionImpl : public CurlAbstraction
	{
		CURL* CurlObject;
		struct curl_slist* RequestHeaders;
		std::string ResponseBody;
		std::string ResponseHeaders;
		std::string RequestBody;
		std::mutex Mutex;

	  public:
		explicit CurlAbstractionImpl();
		~CurlAbstractionImpl() override;
		CurlAbstraction& SetURL(std::string url) override;
		CurlAbstraction& SetHeaders(std::map<std::string, std::string> headers) override;
		CurlAbstraction& SetPostData(std::string postData) override;
		CurlAbstraction& Perform() override;
		std::string GetResponseHeaders() override;
		std::string GetResponseBody() override;
		CurlAbstraction& Reset() override;
		CurlAbstraction& ClearHeaders() override;
		CurlAbstraction& Abort() override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTIONIMPL_H
