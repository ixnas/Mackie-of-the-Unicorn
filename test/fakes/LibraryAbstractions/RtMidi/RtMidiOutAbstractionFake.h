//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTIONFAKE_H
#define MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTIONFAKE_H

#include "../../../../src/LibraryAbstractions/RtMidi/RtMidiOutAbstraction.h"
#include <vector>
#include <optional>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	class RtMidiOutAbstractionFake: public RtMidiOutAbstraction
	{
	  public:
		unsigned int PortCount;
		std::string PortName;
		std::optional<int> GetPortNamePortNumber;
		std::optional<int> OpenPortPort;
		std::vector<std::vector<unsigned char>> SendMessageMessages;

		unsigned int GetPortCount() override
		{
			return PortCount;
		}

		std::string GetPortName(unsigned int portNumber) override
		{
			GetPortNamePortNumber = portNumber;
			return PortName;
		}

		void OpenPort(unsigned int port) override
		{
			OpenPortPort = port;
		}

		void SendMessage(const std::vector<unsigned char>* message) override
		{
			SendMessageMessages.push_back(*message);
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTIONFAKE_H
