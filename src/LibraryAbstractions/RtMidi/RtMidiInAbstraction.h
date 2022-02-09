//
// Created by Sjoerd Scheffer on 09/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTION_H
#define MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTION_H

#include <string>
#include <functional>

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	/// Abstraction for RtMidiIn.
	class RtMidiInAbstraction
	{
	  public:
		virtual ~RtMidiInAbstraction() = default;

		/// Returns the number of available MIDI input ports.
		virtual int GetPortCount() = 0;

		/// Returns the name for a given MIDI input port.
		virtual std::string GetPortName(int port) = 0;

		/// Opens a given MIDI input port.
		virtual void OpenPort(int port) = 0;

		/// Ignore certain MIDI messages.
		virtual void IgnoreTypes(bool sysex, bool timing, bool activeSensing) = 0;

		/// Sets a callback function for whenever the MIDI device sends a message to the application.
		virtual void SetCallBack(std::function<void(double, std::vector<unsigned char>*, void*)>) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_RTMIDIINABSTRACTION_H
