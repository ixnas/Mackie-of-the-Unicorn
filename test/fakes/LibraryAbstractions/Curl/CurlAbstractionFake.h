//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFAKE_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFAKE_H

#include "../../../src/LibraryAbstractions/Curl/CurlAbstraction.h"
#include <sstream>
#include <string>
#include <memory>

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl
{
	class CurlAbstractionFake : public CurlAbstraction
	{
	  public:
		std::optional<std::string> SetURLURL;
		std::optional<std::map<std::string, std::string>> SetHeadersHeaders;
		std::optional<std::string> SetPostDataPostData;
		std::string ResponseHeaders;
		std::string ResponseBody;
		bool Performed = false;
		int ETag;
		std::mutex Mutex;

		~CurlAbstractionFake() override
		{
			std::lock_guard<std::mutex> m(Mutex);
		}

		CurlAbstraction& SetURL(std::string url) override
		{
			std::lock_guard<std::mutex> m(Mutex);
			SetURLURL = url;
			return *this;
		}

		CurlAbstraction& SetHeaders(std::map<std::string, std::string> headers) override
		{
			std::lock_guard<std::mutex> m(Mutex);
			SetHeadersHeaders = headers;
			return *this;
		}

		CurlAbstraction& SetPostData(std::string postData) override
		{
			std::lock_guard<std::mutex> m(Mutex);
			SetPostDataPostData = postData;
			return *this;
		}

		CurlAbstraction& Perform() override
		{
			std::lock_guard<std::mutex> m(Mutex);

			if (SetHeadersHeaders.has_value() && SetHeadersHeaders->contains("If-None-Match") &&
				SetHeadersHeaders.value()["If-None-Match"] >= std::to_string(ETag))
			{
				FakeNoneChangedMessageWithoutMutex();
			}

			Performed = true;
			return *this;
		}

		std::string GetResponseHeaders() override
		{
			std::lock_guard<std::mutex> m(Mutex);
			if (!Performed)
			{
				return {};
			}

			return ResponseHeaders;
		}

		std::string GetResponseBody() override
		{
			std::lock_guard<std::mutex> m(Mutex);
			if (!Performed)
			{
				return {};
			}

			return ResponseBody;
		}

		CurlAbstraction& Reset() override
		{
			std::lock_guard<std::mutex> m(Mutex);
			ClearHeaders();
			SetPostDataPostData.reset();
			return *this;
		}

		CurlAbstraction& ClearHeaders() override
		{
			std::lock_guard<std::mutex> m(Mutex);
			SetHeadersHeaders.reset();
			return *this;
		}

		CurlAbstraction& Abort() override
		{
			std::lock_guard<std::mutex> m(Mutex);
			return *this;
		}

		void FakeNoneChangedMessage()
		{
			std::lock_guard<std::mutex> m(Mutex);
			FakeNoneChangedMessageWithoutMutex();
		}

		void FakeNoneChangedMessageWithoutMutex()
		{
			std::ostringstream stringStream;

			stringStream << "HTTP/1.1 304 Not Modified"
						 << "\r\n";
			stringStream << "Connection: Keep-Alive"
						 << "\r\n";
			stringStream << "Content-Length: 0"
						 << "\r\n";
			stringStream << "Cache-Control: no-cache"
						 << "\r\n";
			stringStream << "Access-Control-Allow-Origin: *"
						 << "\r\n";
			stringStream << "Date: Thu, 01 Jan 1970 00:07:49 GMT"
						 << "\r\n";
			stringStream << "\r\n";

			ResponseBody.clear();
			ResponseHeaders = stringStream.str();
		}

		void FakeHasChangedMessage(int etag, std::string body)
		{
			std::lock_guard<std::mutex> m(Mutex);
			std::ostringstream stringStream;

			stringStream << "HTTP/1.1 200 OK"
			             << "\r\n";
			stringStream << "Connection: Keep-Alive"
			             << "\r\n";
			stringStream << "Transfer-Encoding: chunked"
			             << "\r\n";
			stringStream << "ETag: " << etag << "\r\n";
			stringStream << "Content-Type: application/json"
			             << "\r\n";
			stringStream << "Cache-Control: no-cache"
			             << "\r\n";
			stringStream << "Access-Control-Expose-Headers: Content-Type,ETag"
			             << "\r\n";
			stringStream << "Access-Control-Allow-Origin: *"
			             << "\r\n";
			stringStream << "Date: Thu, 01 Jan 1970 00:08:40 GMT"
			             << "\r\n";
			stringStream << "\r\n";

			ETag = etag;

			ResponseHeaders = stringStream.str();
			ResponseBody = std::move(body);
		}
	};
} // namespace MackieOfTheUnicorn::LibraryAbstractions::Curl

#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFAKE_H
