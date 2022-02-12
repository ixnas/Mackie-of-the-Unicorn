//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTION_H
#define MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTION_H

#include <functional>
#include <string>
#undef SendMessage

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	/// Abstraction for RtMidiOut.
	class RtMidiOutAbstraction
	{
	  public:
		virtual ~RtMidiOutAbstraction() = default;

		/// Returns the number of available MIDI output ports.
		virtual unsigned int GetPortCount() = 0;

		/// Returns the name for a given MIDI output port.
		virtual std::string GetPortName(unsigned int portNumber) = 0;

		/// Opens a given MIDI input port.
		virtual void OpenPort(unsigned int port) = 0;

		/// Sends a MIDI message to the MIDI device.
		virtual void SendMessage(const std::vector<unsigned char>* message) = 0;
	};
} // namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi

#endif // MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTION_H
