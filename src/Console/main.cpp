#include "../Application.h"
#include "../di.h"
#include <curl/curl.h>
#include <sstream>
#include "../LibraryAbstractions/RtMidi/RtMidiInAbstractionImpl.h"
#include "../LibraryAbstractions/RtMidi/RtMidiOutAbstractionImpl.h"
#include "../git_version.h"

MackieOfTheUnicorn::LibraryAbstractions::RtMidi::RtMidiOutAbstractionImpl midiOut;

void mycallback(double deltatime, std::vector<unsigned char>* message, void* userData)
{
	unsigned int nBytes = message->size();
	std::vector<unsigned char> outMessage = {};
	for (unsigned int i = 0; i < nBytes; i++)
		std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
	if (nBytes > 0)
	{
		std::cout << "stamp = " << deltatime << std::endl;
		if ((*message)[0] == 144)
		{
			outMessage = {144, (*message)[1]};
			auto lastByte = (*message)[2] == 127 ? 0 : 127;
			outMessage.push_back(lastByte);
			midiOut.SendMessage(&outMessage);
			outMessage = {0xD0, 0x0B};
			midiOut.SendMessage(&outMessage);
		}
	}
}

int main()
{
	/*
	auto injector = di::make_injector(di::bind<MackieService>().to<MackieServiceImpl>());
	auto app = injector.create<Application>();
	app.Start();
	 */
	MackieOfTheUnicorn::LibraryAbstractions::RtMidi::RtMidiInAbstractionImpl midiIn;

	auto midiInCount = midiIn.GetPortCount();
	auto midiOutCount = midiOut.GetPortCount();

	std::cout << "Inputs: " << midiInCount << std::endl << "Outputs: " << midiOutCount << std::endl << std::endl;

	std::cout << "Input labels:" << std::endl;
	for (auto i = 0; i < midiInCount; i++)
	{
		std::cout << i << ": " << midiIn.GetPortName(i) << std::endl;
	}

	std::cout << "Output labels:" << std::endl;
	for (auto i = 0; i < midiOutCount; i++)
	{
		std::cout << i << ": " << midiOut.GetPortName(i) << std::endl;
	}

	midiIn.OpenPort(0);
	midiIn.SetCallback(&mycallback);
	midiIn.IgnoreTypes(false, false, false);
	midiOut.OpenPort(0);

	// Clear LCD row 1
	std::vector<unsigned char> message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0};
	for (int i = 0; i < 56; i++)
	{
		message.push_back(' ');
	}
	message.push_back(0xF7);
	midiOut.SendMessage(&message);

	// Clear LCD row 2
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
	for (int i = 0; i < 56; i++)
	{
		message.push_back(' ');
	}
	message.push_back(0xF7);
	midiOut.SendMessage(&message);

	// Set LCD message row 1
	std::ostringstream ss;
	ss << "Mackie of the Unicorn " << GIT_VERSION;
	std::string textMessage1 = ss.str();
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0};
	for (int i = 0; i < textMessage1.size(); i++)
	{
		message.push_back(textMessage1[i]);
	}
	message.push_back(0xF7);
	midiOut.SendMessage(&message);

	// Set LCD message row 2
	std::string textMessage2 = "Copyright 2022 Sjoerd Scheffer";
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
	for (int i = 0; i < textMessage2.size(); i++)
	{
		message.push_back(textMessage2[i]);
	}
	message.push_back(0xF7);
	midiOut.SendMessage(&message);

	// Set faders to -inf
	for (unsigned char i = 224; i < 233; i++)
	{
		message = {i, 0, 0};
		midiOut.SendMessage(&message);
	}

	for (unsigned char i = 0; i < 113; i++)
	{
		message = {144, i, 127};
		midiOut.SendMessage(&message);
	}

	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x20, 0x01, 0b00000100, 0xF7};
	midiOut.SendMessage(&message);
	message = {0xF0, 0x00, 0x00, 0x66, 0x14, 0x21, 0x01, 0xF7};
	midiOut.SendMessage(&message);

	getchar();
}
