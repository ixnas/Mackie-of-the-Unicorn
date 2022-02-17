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

	CurlAbstractionImpl::CurlAbstractionImpl() : list(nullptr), curl(curl_easy_init())
	{
	}

	CurlAbstractionImpl::~CurlAbstractionImpl()
	{
		if (list != nullptr)
		{
			curl_slist_free_all(list);
			list = nullptr;
		}
		curl_easy_cleanup(curl);
	}

	void CurlAbstractionImpl::SetURL(std::string url)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerBuffer);
	}

	void CurlAbstractionImpl::SetHeaders(std::map<std::string, std::string> headers)
	{
		for (const auto& header : headers)
		{
			std::ostringstream headerStringBuffer;
			headerStringBuffer << header.first << ": " << header.second;
			auto headerString = headerStringBuffer.str();
			list = curl_slist_append(list, headerString.c_str());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	}

	void CurlAbstractionImpl::SetPostData(std::string postData)
	{
		this->postData = postData;
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, this->postData.c_str());
	}

	void CurlAbstractionImpl::Perform()
	{
		curl_easy_perform(curl);
	}

	std::string CurlAbstractionImpl::GetResponseHeaders()
	{
		return headerBuffer;
	}

	std::string CurlAbstractionImpl::GetResponseBody()
	{
		return readBuffer;
	}

	void CurlAbstractionImpl::Reset()
	{
		ClearHeaders();
		headerBuffer.clear();
		readBuffer.clear();
		curl_easy_reset(curl);
	}

	void CurlAbstractionImpl::ClearHeaders()
	{
		if (list != nullptr)
		{
			curl_slist_free_all(list);
			list = nullptr;
		}
	}
}
