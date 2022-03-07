//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H

#include "../../../src/Mackie/MackieDevice.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDeviceFake : public MackieDevice
	{
	  public:
		MackieListener<MackieDevice>* MackieListener;
		std::optional<int> SetChannelMuteChannelNumber;
		std::optional<int> SetChannelMuteOn;

		std::optional<int> SetChannelSoloChannelNumber;
		std::optional<int> SetChannelSoloOn;

		void SetMackieListener(Mackie::MackieListener<MackieDevice>& mackieListener) override
		{
			MackieListener = &mackieListener;
		}

		void SetChannelMute(int channelNumber, bool on) override
		{
			SetChannelMuteChannelNumber = channelNumber;
			SetChannelMuteOn = on;
			MackieListener->OnChannelMutePressed(this, channelNumber, on);
		}

		void SetChannelSolo(int channelNumber, bool on) override
		{
			SetChannelSoloChannelNumber = channelNumber;
			SetChannelSoloOn = on;
			MackieListener->OnChannelSoloPressed(this, channelNumber, on);
		}

		void MIDICallback(std::vector<unsigned char>& message) override
		{
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
