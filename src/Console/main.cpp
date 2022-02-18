#include "../Application.h"
#include "../LibraryAbstractions/Curl/CurlAbstractionImpl.h"
#include "../LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryImpl.h"
#include "../LibraryAbstractions/RtMidi/RtMidiInAbstractionImpl.h"
#include "../LibraryAbstractions/RtMidi/RtMidiOutAbstractionImpl.h"
#include "../MIDI/Factories/MIDIDeviceFactoryImpl.h"
#include "../MIDI/MIDIServiceImpl.h"
#include "../Mackie/Factories/MackieCompositeFactoryImpl.h"
#include "../Mackie/Factories/MackieDeviceFactoryImpl.h"
#include "../Mackie/MackieServiceImpl.h"
#include "../JSON/JSONValue.h"
#include "../di.h"
#include "../git_version.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "../HTTP/ETagParser.h"
#include "../JSON/JSONSerializer.h"
#include <curl/curl.h>
#include <future>
#include <sstream>

class HTTPListener
{
  public:
	virtual ~HTTPListener() = default;
	virtual void HTTPCallback(std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>& message) = 0;

};

class HTTPDevice
{
	HTTPListener* Listener;
	MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstraction* CurlIn;
	MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstraction* CurlOut;
	bool Running;
	std::future<void> Task;

	void Loop()
	{
		std::optional<int> etag;
		while (Running)
		{
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
			auto newEtag = MackieOfTheUnicorn::HTTP::ETagParser::GetETag(responseHeaders);

			// Continue if there weren't any changes.
			if (!newEtag.has_value())
			{
				continue;
			}

			etag = newEtag;

			auto pairs = MackieOfTheUnicorn::JSON::JSONSerializer::Parse(responseBody);

			// Call callback for every key/value pair.
			for (auto& pair : pairs)
			{
				Listener->HTTPCallback(pair);
			}
			std::cout << responseHeaders << std::endl << etag.value() << std::endl;
		}
	}

  public:
	explicit HTTPDevice(MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstraction& curlIn,
	                    MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstraction& curlOut)
	    : Listener(nullptr), CurlIn(&curlIn), CurlOut(&curlOut), Running(false)
	{
	}

	~HTTPDevice()
	{
		if(Task.valid())
		{
			Running = false;
			CurlIn->Abort();
			Task.wait();
		}
	}

	void StartListening()
	{
		Running = true;
		Task = std::async(std::launch::async, &HTTPDevice::Loop, this);
	}

	void StopListening()
	{
		Running = false;
		CurlIn->Abort();
		Task.wait();
	}

	void RegisterCallback(HTTPListener& listener)
	{
		Listener = &listener;
	}

	void SendMessage(std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>& message)
	{
		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> objects = {message};
		auto messageString = MackieOfTheUnicorn::JSON::JSONSerializer::Serialize(objects);

		CurlOut->SetPostData(messageString);
		CurlOut->Perform();
	}
};

class HTTPListenerImpl : public HTTPListener
{
	void HTTPCallback(std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>& message) override
	{
		auto value = message.second;
		if (value.Float.has_value())
		{
			std::cout << message.first << ": " << value.Float.value() << std::endl;
		}
		else if (value.Integer.has_value())
		{
			std::cout << message.first << ": " << value.Integer.value() << std::endl;
		}
		else if (value.String.has_value())
		{
			std::cout << message.first << ": " << value.String.value() << std::endl;
		}
	}
};

int main()
{
	MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionImpl curlIn;
	curlIn.SetURL("http://localhost:8080/datastore");
	MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionImpl curlOut;
	curlIn.SetURL("http://localhost:8080/datastore");

	HTTPDevice restDevice(curlIn, curlOut);
	HTTPListenerImpl restListener;
	restDevice.RegisterCallback(restListener);
	restDevice.StartListening();
	std::this_thread::sleep_for(std::chrono::seconds(500));
	std::cout << "Stop" << std::endl;
	restDevice.StopListening();

	return 0;
	MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionImpl curlAbstraction;
	auto response = curlAbstraction.SetURL("http://localhost:8080/datastore").Perform().GetResponseBody();
	auto headers = curlAbstraction.GetResponseHeaders();

	auto start = std::chrono::system_clock::now();
	rapidjson::Document document;
	document.Parse(response.c_str());
	auto end = std::chrono::system_clock::now();
	auto diff = end - start;
	std::cout << "rapidjson " << std::chrono::duration<double>(diff).count() << std::endl;

	start = std::chrono::system_clock::now();
	auto doc = MackieOfTheUnicorn::JSON::JSONSerializer::Parse(response);
	end = std::chrono::system_clock::now();
	diff = end - start;
	std::cout << "JSONSerializer " << std::chrono::duration<double>(diff).count() << std::endl;

	return 0;
	std::cout << "Mackie of the Unicorn " << MackieOfTheUnicorn::VERSION << std::endl
	          << "Copyright \u00a9 2022 Sjoerd Scheffer" << std::endl
	          << std::endl;
	auto injector = di::make_injector(
	    di::bind<MackieOfTheUnicorn::Mackie::MackieService>.to<MackieOfTheUnicorn::Mackie::MackieServiceImpl>(),
	    di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactoryImpl>(),
	    di::bind<MackieOfTheUnicorn::MIDI::MIDIService>.to<MackieOfTheUnicorn::MIDI::MIDIServiceImpl>(),
	    di::bind<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactory>.to<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryImpl>(),
	    di::bind<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory>.to<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryImpl>(),
	    di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryImpl>());
	auto app = injector.create<MackieOfTheUnicorn::Application>();
	auto inputDevices = app.GetAvailableInputDevices();
	auto outputDevices = app.GetAvailableOutputDevices();

	std::cout << "Input devices:" << std::endl;
	for (const auto& inputDevice : inputDevices)
	{
		std::cout << inputDevice.first << ": " << inputDevice.second << std::endl;
	}

	std::cout << std::endl << "Output devices:" << std::endl;
	for (const auto& outputDevice : outputDevices)
	{
		std::cout << outputDevice.first << ": " << outputDevice.second << std::endl;
	}

	std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
	app.Start(inputAndOutputIds);

	getchar();
}
