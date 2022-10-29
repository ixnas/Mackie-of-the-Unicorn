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

	void MackieCompositeImpl::SetChannelSolo(int channelNumber, bool on)
	{
		for (const auto& mackieDevice : MackieDevices)
		{
			mackieDevice->SetChannelSolo(channelNumber, on);
		}
	}

	void MackieCompositeImpl::OnChannelSoloPressed(MackieDevice* origin, int channelId, bool on)
	{
		MackieListener->OnChannelSoloPressed(this, channelId, on);
	}

	void MackieCompositeImpl::SetChannelText(int channelNumber, bool onBottomRow, std::string_view text)
	{
		for (const auto& mackieDevice : MackieDevices)
		{
			mackieDevice->SetChannelText(channelNumber, onBottomRow, text);
		}
	}

	void MackieCompositeImpl::OnBankForwardPressed()
	{
		MackieListener->OnBankForwardPressed();
	}

	void MackieCompositeImpl::OnBankBackwardsPressed()
	{
		MackieListener->OnBankBackwardsPressed();
	}
}
