//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "MOTUMixer.h"
#include "../HTTP/HTTPDevice.h"

namespace MackieOfTheUnicorn::Mixers
{
	MOTUMixer::MOTUMixer(std::unique_ptr<HTTP::HTTPDevice> httpDevice)
	    : HTTPDevice(std::move(httpDevice)), VirtualMixer(nullptr)
	{
	}

	void MOTUMixer::SetVirtualMixer(Mixers::VirtualMixer* virtualMixer)
	{
	}

	int MOTUMixer::GetId()
	{
		return 0;
	}

	void MOTUMixer::SetInputChannelMute(int originId, int channel, bool on)
	{
	}
} // namespace MackieOfTheUnicorn::Mixers
