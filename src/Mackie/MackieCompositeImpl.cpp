//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "MackieCompositeImpl.h"
#include "MackieDevice.h"

namespace MackieOfTheUnicorn::Mackie
{
	MackieCompositeImpl::MackieCompositeImpl(std::vector<std::unique_ptr<MackieDevice>>& mackieDevices) : MackieDevices(std::move(mackieDevices))
	{
	}

	void MackieCompositeImpl::SetChannelMute(int channelNumber, bool on)
	{
		for (const auto& mackieDevice : MackieDevices)
		{
			mackieDevice->SetChannelMute(channelNumber, on);
		}
	}

	void MackieCompositeImpl::OnSetChannelMute(MackieDevice* origin, int channelId, bool on)
	{
	}
}
