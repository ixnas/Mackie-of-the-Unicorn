//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTIONIMPL_H
#define MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTIONIMPL_H

#include "../../../ext/rtmidi/RtMidi.h"
#include "RtMidiInAbstraction.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	class RtMidiInAbstractionImpl : RtMidiInAbstraction
	{
		RtMidiIn RtMidiIn;

	  public:
		unsigned int GetPortCount() override;
		std::string GetPortName(unsigned int portNumber) override;
		void OpenPort(unsigned int portNumber) override;
		void IgnoreTypes(bool midiSysex, bool midiTime, bool midiSense) override;
		void SetCallback(void (*callback)(double, std::vector<unsigned char>*, void*)) override;
	};
} // namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi

#endif // MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTIONIMPL_H
