//
// Created by Sjoerd Scheffer on 17/02/2022.
//

#include "CurlAbstractionImpl.h"

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
		curl_easy_setopt(CurlObject, CURLOPT_TIMEOUT_MS, 1);
		std::lock_guard<std::mutex> lock(Mutex);

		if (RequestHeaders != nullptr)
		{
			curl_slist_free_all(RequestHeaders);
			RequestHeaders = nullptr;
		}
		curl_easy_cleanup(CurlObject);
	}

	CurlAbstraction& CurlAbstractionImpl::SetURL(std::string url)
	{
		std::lock_guard<std::mutex> lock(Mutex);

		curl_easy_setopt(CurlObject, CURLOPT_URL, url.c_str());

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::SetHeaders(std::map<std::string, std::string> headers)
	{
		std::lock_guard<std::mutex> lock(Mutex);

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
		std::lock_guard<std::mutex> lock(Mutex);

		this->RequestBody = postData;
		curl_easy_setopt(CurlObject, CURLOPT_POSTFIELDS, this->RequestBody.c_str());

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::Perform()
	{
		std::lock_guard<std::mutex> lock(Mutex);

		ResponseBody.clear();
		ResponseHeaders.clear();
		curl_easy_setopt(CurlObject, CURLOPT_WRITEFUNCTION, &Callback);
		curl_easy_setopt(CurlObject, CURLOPT_WRITEDATA, &ResponseBody);
		curl_easy_setopt(CurlObject, CURLOPT_HEADERDATA, &ResponseHeaders);
		curl_easy_perform(CurlObject);

		return *this;
	}

	std::string CurlAbstractionImpl::GetResponseHeaders()
	{
		std::lock_guard<std::mutex> lock(Mutex);

		return ResponseHeaders;
	}

	std::string CurlAbstractionImpl::GetResponseBody()
	{
		std::lock_guard<std::mutex> lock(Mutex);

		return ResponseBody;
	}

	CurlAbstraction& CurlAbstractionImpl::Reset()
	{
		ClearHeaders();

		std::lock_guard<std::mutex> lock(Mutex);
		ResponseHeaders.clear();
		ResponseBody.clear();
		curl_easy_reset(CurlObject);

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::ClearHeaders()
	{
		std::lock_guard<std::mutex> lock(Mutex);

		if (RequestHeaders != nullptr)
		{
			curl_slist_free_all(RequestHeaders);
			RequestHeaders = nullptr;
		}

		return *this;
	}

	CurlAbstraction& CurlAbstractionImpl::Abort()
	{
		curl_easy_setopt(CurlObject, CURLOPT_TIMEOUT_MS, 1);
		std::lock_guard<std::mutex> lock(Mutex);
		curl_easy_setopt(CurlObject, CURLOPT_TIMEOUT_MS, 0);

		return *this;
	}
}
