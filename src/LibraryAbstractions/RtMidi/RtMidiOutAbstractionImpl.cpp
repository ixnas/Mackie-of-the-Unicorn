//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#include "RtMidiOutAbstractionImpl.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	unsigned int RtMidiOutAbstractionImpl::GetPortCount()
	{
		return RtMidiOut.getPortCount();
	}

	std::string RtMidiOutAbstractionImpl::GetPortName(unsigned int portNumber)
	{
		return RtMidiOut.getPortName(portNumber);
	}

	void RtMidiOutAbstractionImpl::OpenPort(unsigned int port)
	{
		RtMidiOut.openPort(port);
	}

	void RtMidiOutAbstractionImpl::SendMessage(const std::vector<unsigned char>* message)
	{
		RtMidiOut.sendMessage(message);
	}
} // namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
