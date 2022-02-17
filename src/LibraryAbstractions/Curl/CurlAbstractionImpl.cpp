//
// Created by Sjoerd Scheffer on 17/02/2022.
//

#include "CurlAbstractionImpl.h"
#include <sstream>

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl
{
	static size_t Callback(char *contents, size_t size, size_t nmemb, std::string *s)
	{
		size_t newLength = size*nmemb;
		try
		{
			s->append((char*)contents, newLength);
		}
		catch(std::bad_alloc &e)
		{
			return 0;
		}
		return newLength;
	}

	CurlAbstractionImpl::CurlAbstractionImpl() : RequestHeaders(nullptr), CurlObject(curl_easy_init())
	{
	}

	CurlAbstractionImpl::~CurlAbstractionImpl()
	{
		if (RequestHeaders != nullptr)
		{
			curl_slist_free_all(RequestHeaders);
			RequestHeaders = nullptr;
		}
		curl_easy_cleanup(CurlObject);
	}

	CurlAbstraction& CurlAbstractionImpl::SetURL(std::string url)
	{
		curl_easy_setopt(CurlObject, CURLOPT_URL, url.c_str());
		curl_easy_setopt(CurlObject, CURLOPT_WRITEFUNCTION, &Callback);
		curl_easy_setopt(CurlObject, CURLOPT_WRITEDATA, &ResponseBody);
		curl_easy_setopt(CurlObject, CURLOPT_HEADERDATA, &ResponseHeaders);

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::SetHeaders(std::map<std::string, std::string> headers)
	{
		for (const auto& header : headers)
		{
			std::ostringstream headerStringBuffer;
			headerStringBuffer << header.first << ": " << header.second;
			auto headerString = headerStringBuffer.str();
			RequestHeaders = curl_slist_append(RequestHeaders, headerString.c_str());
		}

		curl_easy_setopt(CurlObject, CURLOPT_HTTPHEADER, RequestHeaders);

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::SetPostData(std::string postData)
	{
		this->RequestBody = postData;
		curl_easy_setopt(CurlObject, CURLOPT_POSTFIELDS, this->RequestBody.c_str());

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::Perform()
	{
		curl_easy_perform(CurlObject);

		return *this;
	}

	std::string CurlAbstractionImpl::GetResponseHeaders()
	{
		return ResponseHeaders;
	}

	std::string CurlAbstractionImpl::GetResponseBody()
	{
		return ResponseBody;
	}

	CurlAbstraction& CurlAbstractionImpl::Reset()
	{
		ClearHeaders();
		ResponseHeaders.clear();
		ResponseBody.clear();
		curl_easy_reset(CurlObject);

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::ClearHeaders()
	{
		if (RequestHeaders != nullptr)
		{
			curl_slist_free_all(RequestHeaders);
			RequestHeaders = nullptr;
		}

		return *this;
	}
}
