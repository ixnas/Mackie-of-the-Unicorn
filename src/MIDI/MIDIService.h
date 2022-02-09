//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIDISERVICE_H
#define MACKIE_OF_THE_UNICORN_MIDISERVICE_H

#include <map>
#include <string>

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDevice;

	/// Service used to get connected MIDI devices.
	class MIDIService
	{
	  public:
		virtual ~MIDIService() = default;
		virtual std::map<int, std::string> GetInputDevices() = 0;
		virtual std::map<int, std::string> GetOutputDevices() = 0;
		virtual std::unique_ptr<MIDIDevice> GetMIDIDevice(int inputId, int outputId) = 0;
	};
} // namespace MackieOfTheUnicorn::MIDI

#endif // MACKIE_OF_THE_UNICORN_MIDISERVICE_H
