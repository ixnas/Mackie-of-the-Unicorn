//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H

#include "../../../src/Mackie/MackieDevice.h"
#include <optional>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDeviceFake : public MackieDevice
	{
	  public:
		MackieListener* MackieListener;
		std::optional<int> SetChannelMuteChannelNumber;
		std::optional<int> SetChannelMuteOn;

		void SetMackieListener(Mackie::MackieListener& mackieListener) override
		{
			MackieListener = &mackieListener;
		}

		void SetChannelMute(int channelNumber, bool on) override
		{
			SetChannelMuteChannelNumber = channelNumber;
			SetChannelMuteOn = on;
		}

		void MIDICallback(std::vector<unsigned char>& message) override
		{
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
