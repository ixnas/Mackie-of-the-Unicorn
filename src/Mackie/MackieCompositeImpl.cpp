//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "MackieCompositeImpl.h"
#include "MackieDevice.h"

namespace MackieOfTheUnicorn::Mackie
{
	MackieCompositeImpl::MackieCompositeImpl(std::vector<std::unique_ptr<MackieDevice>>& mackieDevices) : MackieDevices(std::move(mackieDevices))
	{
		for (const auto& mackieDevice : MackieDevices)
		{
			mackieDevice->SetMackieListener(*this);
		}
	}

	void MackieCompositeImpl::SetChannelMute(int channelNumber, bool on)
	{
		for (const auto& mackieDevice : MackieDevices)
		{
			mackieDevice->SetChannelMute(channelNumber, on);
		}
	}

	void MackieCompositeImpl::OnChannelMutePressed(MackieDevice* origin, int channelId, bool on)
	{
		MackieListener->OnChannelMutePressed(this, channelId, on);
	}

	void MackieCompositeImpl::SetMackieListener(Mackie::MackieListener<MackieComposite>& mackieListener)
	{
		MackieListener = &mackieListener;
	}
}
