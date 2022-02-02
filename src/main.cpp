#include <thread>
#include "Application.h"
#include "RtMidi.h"
#include "di.h"
#include <curl/curl.h>

RtMidiOut midiOut;

void mycallback(double deltatime, std::vector<unsigned char>* message, void* userData)
{
	unsigned int nBytes = message->size();
	for (unsigned int i = 0; i < nBytes; i++)
		std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
	if (nBytes > 0)
	{
		std::cout << "stamp = " << deltatime << std::endl;
	}
}

int main()
{
	/*
	auto injector = di::make_injector(di::bind<MackieService>().to<MackieServiceImpl>());
	auto app = injector.create<Application>();
	app.Start();
	 */
	RtMidiIn midiIn;

	auto midiInCount = midiIn.getPortCount();
	auto midiOutCount = midiOut.getPortCount();

	std::cout << "Inputs: " << midiInCount << std::endl << "Outputs: " << midiOutCount << std::endl << std::endl;

	std::cout << "Input labels:" << std::endl;
	for (auto i = 0; i < midiInCount; i++)
	{
		std::cout << i << ": " << midiIn.getPortName(i) << std::endl;
	}

	std::cout << "Output labels:" << std::endl;
	for (auto i = 0; i < midiOutCount; i++)
	{
		std::cout << i << ": " << midiOut.getPortName(i) << std::endl;
	}

	midiIn.openPort(0);
	midiIn.setCallback(&mycallback);
	midiIn.ignoreTypes(false, false, false);
	midiOut.openPort(0);

	// Clear LCD row 1
	std::vector<unsigned char> message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0};
	for (int i = 0; i < 56; i++)
	{
		message.push_back(' ');
	}
	message.push_back(0xF7);
	midiOut.sendMessage(&message);

	// Clear LCD row 2
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
	for (int i = 0; i < 56; i++)
	{
		message.push_back(' ');
	}
	message.push_back(0xF7);
	midiOut.sendMessage(&message);


	// Set LCD message row 1
	std::string textMessage1 = "Mackie of the Unicorn";
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0};
	for(int i = 0; i < textMessage1.size(); i++)
	{
		message.push_back(textMessage1[i]);
	}
	message.push_back(0xF7);
	midiOut.sendMessage(&message);

	// Set LCD message row 2
	std::string textMessage2 = "Copyright 2022 Sjoerd Scheffer";
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
	for(int i = 0; i < textMessage2.size(); i++)
	{
		message.push_back(textMessage2[i]);
	}
	message.push_back(0xF7);
	midiOut.sendMessage(&message);

	// Set faders to -inf
	for(int i = 224; i < 233; i++)
	{
		message.push_back(i);
		message.push_back(0);
		message.push_back(0);
		midiOut.sendMessage(&message);
	}

	getchar();
}
