//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTIONIMPL_H
#define MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTIONIMPL_H

#include "../../../ext/rtmidi/RtMidi.h"
#include "RtMidiOutAbstraction.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	class RtMidiOutAbstractionImpl : public RtMidiOutAbstraction
	{
		RtMidiOut RtMidiOut;

	  public:
		unsigned int GetPortCount() override;
		std::string GetPortName(unsigned int portNumber) override;
		void OpenPort(unsigned int port) override;
		void SendMessage(const std::vector<unsigned char>* message) override;
	};
} // namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi

#endif // MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTIONIMPL_H
