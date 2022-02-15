//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#include "MackieDeviceImpl.h"

namespace MackieOfTheUnicorn::Mackie
{
	static bool IsChannelMuteMessage(std::vector<unsigned char>& message)
	{
		return message[0] == 144 && message[1] >= 16 &&
		       message[1] < 24 &&
		       (message[2] == 127 || message[2] == 0);
	}

	MackieDeviceImpl::MackieDeviceImpl(std::unique_ptr<MIDI::MIDIDevice>& midiDevice) : MIDIDevice(std::move(midiDevice))
	{
		MIDIDevice->RegisterCallback(this);
	}

	void MackieDeviceImpl::SetMackieListener(Mackie::MackieListener<MackieDevice>& mackieListener)
	{
		MackieListener = &mackieListener;
	}

	void MackieDeviceImpl::SetChannelMute(int channelNumber, bool on)
	{
		const unsigned char byte1 = 144;
		unsigned char byte2 = 16 + channelNumber;
		unsigned char byte3 = on ? 127 : 0;
		std::vector<unsigned char> message = {byte1, byte2, byte3};

		MIDIDevice->SendMessage(message);
	}

	void MackieDeviceImpl::MIDICallback(std::vector<unsigned char>& message)
	{
		if (IsChannelMuteMessage(message))
		{
			auto channelId = message[1] - 16;
			auto on = message[2] == 127;
			MackieListener->OnSetChannelMute(this, channelId, on);
		}
	}
}