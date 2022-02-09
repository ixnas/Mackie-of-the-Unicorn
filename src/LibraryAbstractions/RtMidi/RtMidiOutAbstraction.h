//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTION_H
#define MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTION_H

#include <string>
#include <functional>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	/// Abstraction for RtMidiOut.
	class RtMidiOutAbstraction
	{
	  public:
		virtual ~RtMidiOutAbstraction() = default;

		/// Returns the number of available MIDI output ports.
		virtual int GetPortCount() = 0;

		/// Returns the name for a given MIDI output port.
		virtual std::string GetPortName() = 0;

		/// Opens a given MIDI input port.
		virtual void OpenPort(int port) = 0;

		/// Sends a MIDI message to the MIDI device.
		virtual void SendMessage(std::vector<unsigned char>* message) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_RTMIDIOUTABSTRACTION_H
