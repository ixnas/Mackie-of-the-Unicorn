//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORY_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORY_H

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIDevice;
}

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;
}

namespace MackieOfTheUnicorn::Mackie::Factories
{
	/// Creates Mackie device interfaces using a MIDI device.
	class MackieDeviceFactory
	{
	  public:
		virtual ~MackieDeviceFactory() = default;

		/// Returns a new Mackie device using a MIDI device.
		virtual std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDI::MIDIDevice>& midiDevice) = 0;
	};
} // namespace MackieOfTheUnicorn::Mackie::Factories

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFACTORY_H
