//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#include "RtMidiInAbstractionImpl.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	unsigned int RtMidiInAbstractionImpl::GetPortCount()
	{
		return RtMidiIn.getPortCount();
	}

	std::string RtMidiInAbstractionImpl::GetPortName(unsigned int portNumber)
	{
		return RtMidiIn.getPortName(portNumber);
	}

	void RtMidiInAbstractionImpl::OpenPort(unsigned int portNumber)
	{
		RtMidiIn.openPort(portNumber);
	}

	void RtMidiInAbstractionImpl::IgnoreTypes(bool midiSysex, bool midiTime, bool midiSense)
	{
		RtMidiIn.ignoreTypes(midiSysex, midiTime, midiSense);
	}

	void RtMidiInAbstractionImpl::SetCallback(void (*callback)(double, std::vector<unsigned char>*, void*), void* userData)
	{
		RtMidiIn.setCallback(callback, userData);
	}
} // namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi