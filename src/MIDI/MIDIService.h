//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDISERVICE_H
#define MACKIE_OF_THE_UNICORN_MIDISERVICE_H

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDevice;

	/// Service used to get connected MIDI devices.
	class MIDIService
	{
	  public:
		virtual ~MIDIService() = default;

		/// Returns a list of available MIDI input devices.
		virtual std::map<int, std::string> GetInputDevices() = 0;

		/// Returns a list of available MIDI input devices.
		virtual std::map<int, std::string> GetOutputDevices() = 0;

		/// Returns a bi-directional MIDI device for the given input and output port IDs.
		virtual std::unique_ptr<MIDIDevice> GetMIDIDevice(int inputId, int outputId) = 0;
	};
} // namespace MackieOfTheUnicorn::MIDI

#endif // MACKIE_OF_THE_UNICORN_MIDISERVICE_H
