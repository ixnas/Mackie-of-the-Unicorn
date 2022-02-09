//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTION_H
#define MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTION_H

#include <functional>
#include <string>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	/// Abstraction for RtMidiIn.
	class RtMidiInAbstraction
	{
	  public:
		virtual ~RtMidiInAbstraction() = default;

		/// Returns the number of available MIDI input ports.
		virtual unsigned int GetPortCount() = 0;

		/// Returns the name for a given MIDI input port.
		virtual std::string GetPortName(unsigned int portNumber) = 0;

		/// Opens a given MIDI input port.
		virtual void OpenPort(unsigned int portNumber) = 0;

		/// Ignore certain MIDI messages.
		virtual void IgnoreTypes(bool midiSysex, bool midiTime, bool midiSense) = 0;

		/// Sets a callback function for whenever the MIDI device sends a message to the application.
		virtual void SetCallback(void (*callback)(double, std::vector<unsigned char>*, void*)) = 0;
	};
} // namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi

#endif // MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTION_H
