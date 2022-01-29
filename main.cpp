#include "RtMidi.h"
#include "di.h"
#include "rapidjson/document.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int main()
{
	std::string jsonString = "{\"value\":\"yes\"}";
	rapidjson::Document doc;
	doc.Parse(jsonString.c_str());
	rapidjson::Value& val = doc["value"];
	std::string output = val.GetString();
	CURL* curl;
	CURLcode res;
	std::string readBuffer;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	std::cout << readBuffer << std::endl;
	try
	{
		auto midiin = std::make_unique<RtMidiIn>();
		auto nPorts = midiin->getPortCount();
		std::cout << nPorts << std::endl;
	}
	catch (RtMidiError& e)
	{
		e.printMessage();
	}
	std::cout << "Hello, World!" << std::endl << output << std::endl;
	return 0;
}
