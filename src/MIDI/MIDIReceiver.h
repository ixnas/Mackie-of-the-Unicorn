//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDIRECEIVER_H
#define MACKIE_OF_THE_UNICORN_MIDIRECEIVER_H

namespace MackieOfTheUnicorn::MIDI
{
	/// Interface for classes that implement a callback to receive MIDI messages.
	class MIDIReceiver
	{
	  public:
		virtual ~MIDIReceiver() = default;

		/// The callback function that will be called with the MIDI message as a parameter.
		virtual void MIDICallback(std::vector<unsigned char>& message) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIDIRECEIVER_H
