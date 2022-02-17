//
// Created by Sjoerd Scheffer on 17/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTIONIMPL_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTIONIMPL_H

#include "CurlAbstraction.h"
#include <curl/curl.h>

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl
{
	class CurlAbstractionImpl : public CurlAbstraction
	{
		CURL* curl;
		struct curl_slist* list;
		std::string readBuffer;
		std::string headerBuffer;
		std::string postData;

	  public:
		explicit CurlAbstractionImpl();
		~CurlAbstractionImpl() override;
		void SetURL(std::string url) override;
		void SetHeaders(std::map<std::string, std::string> headers) override;
		void SetPostData(std::string postData) override;
		void Perform() override;
		std::string GetResponseHeaders() override;
		std::string GetResponseBody() override;
		void Reset() override;
		void ClearHeaders() override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTIONIMPL_H
