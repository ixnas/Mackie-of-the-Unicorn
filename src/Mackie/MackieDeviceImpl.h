//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEIMPL_H

#include "MackieDevice.h"
#include "../MIDI/MIDIDevice.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDeviceImpl : public MackieDevice
	{
		std::unique_ptr<MIDI::MIDIDevice> MIDIDevice;
		MackieListener<MackieDevice>* MackieListener;

	  public:
		explicit MackieDeviceImpl(std::unique_ptr<MIDI::MIDIDevice>& midiDevice);
		void SetMackieListener(Mackie::MackieListener<MackieDevice>& mackieListener) override;
		void SetChannelMute(int channelNumber, bool on) override;
		void SetChannelSolo(int channelNumber, bool on) override;
		void MIDICallback(std::vector<unsigned char>& message) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEIMPL_H
