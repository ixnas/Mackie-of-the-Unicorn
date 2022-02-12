//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTIONFAKE_H
#define MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTIONFAKE_H

#include "../../../../src/LibraryAbstractions/RtMidi/RtMidiInAbstraction.h"
#include <optional>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	class RtMidiInAbstractionFake: public RtMidiInAbstraction
	{
	  public:
		unsigned int PortCount;
		std::string PortName;
		std::optional<unsigned int> OpenPortPort;
		std::optional<bool> IgnoreTypesMidiSysex;
		std::optional<bool> IgnoreTypesMidiTime;
		std::optional<bool> IgnoreTypesMidiSense;
		void (*SetCallbackCallback)(double, std::vector<unsigned char>*, void*) = nullptr;
		void* SetCallbackUserData = nullptr;

		unsigned int GetPortCount() override
		{
			return PortCount;
		}

		std::string GetPortName(unsigned int portNumber) override
		{
			return PortName;
		}

		void OpenPort(unsigned int portNumber) override
		{
			OpenPortPort = portNumber;
		}

		void IgnoreTypes(bool midiSysex, bool midiTime, bool midiSense) override
		{
			IgnoreTypesMidiSysex = midiSysex;
			IgnoreTypesMidiTime = midiTime;
			IgnoreTypesMidiSense = midiSense;
		}

		void SetCallback(void (*callback)(double, std::vector<unsigned char>*, void*), void* userData) override
		{
			SetCallbackCallback = callback;
			SetCallbackUserData = userData;
		}

		void FakeMessage(double deltaTime, std::vector<unsigned char>& message) const
		{
			SetCallbackCallback(deltaTime, &message, SetCallbackUserData);
		}
	};
}
#endif // MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTIONFAKE_H
