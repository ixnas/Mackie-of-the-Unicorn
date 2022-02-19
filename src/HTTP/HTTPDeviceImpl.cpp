//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "HTTPDeviceImpl.h"
#include "HTTPListener.h"
#include "../JSON/JSONSerializer.h"
#include "ETagParser.h"

namespace MackieOfTheUnicorn::HTTP
{
	void HTTPDeviceImpl::Loop()
	{
		// Prevent early exit race condition, especially for unit tests.
		bool firstRound = true;
		std::optional<int> etag;

		while (Running || firstRound)
		{
			firstRound = false;

			CurlIn->ClearHeaders();
			// Only get changes after first round.
			if (etag.has_value())
			{
				CurlIn->SetHeaders({{"If-None-Match", std::to_string(etag.value())}});
			}

			// Perform request.
			CurlIn->Perform();
			auto responseBody = CurlIn->GetResponseBody();
			auto responseHeaders = CurlIn->GetResponseHeaders();

			// Try to parse ETag (there were changes).
			auto newEtag = ETagParser::GetETag(responseHeaders);

			// Continue if there weren't any changes.
			if (!newEtag.has_value())
			{
				continue;
			}

			etag = newEtag;

			auto pairs = JSON::JSONSerializer::Parse(responseBody);

			// Call callback for every key/value pair.
			for (auto& pair : pairs)
			{
				Listener->HTTPCallback(pair);
			}
		}
	}

	HTTPDeviceImpl::HTTPDeviceImpl(std::unique_ptr<LibraryAbstractions::Curl::CurlAbstraction> curlIn,
	                               std::unique_ptr<LibraryAbstractions::Curl::CurlAbstraction> curlOut)
		: Listener(nullptr), CurlIn(std::move(curlIn)), CurlOut(std::move(curlOut)), Running(false)
	{
	}

	HTTPDeviceImpl::~HTTPDeviceImpl()
	{
		if(Task.valid())
		{
			Running = false;
			CurlIn->Abort();
			Task.wait();
		}
	}

	void HTTPDeviceImpl::StartListening()
	{
		Running = true;
		Task = std::async(std::launch::async, &HTTPDeviceImpl::Loop, this);
	}

	void HTTPDeviceImpl::StopListening()
	{
		Running = false;
		CurlIn->Abort();
		Task.wait();
	}

	void HTTPDeviceImpl::RegisterCallback(HTTPListener& listener)
	{
		Listener = &listener;
	}

	void HTTPDeviceImpl::SendMessage(std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>& message)
	{
		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> objects = {message};
		auto messageString = MackieOfTheUnicorn::JSON::JSONSerializer::Serialize(objects);

		CurlOut->SetPostData(messageString);
		CurlOut->Perform();
	}
}
