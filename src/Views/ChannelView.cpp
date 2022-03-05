//
// Created by Sjoerd Scheffer on 04/03/2022.
//

#include "ChannelView.h"

namespace MackieOfTheUnicorn::Views
{
	ChannelView::ChannelView(MackieViewData& viewData) : ViewData(viewData), MackieComposite(nullptr), VirtualMixer(nullptr)
	{
	}

	void ChannelView::SetVirtualMixer(Mixers::VirtualMixer& virtualMixer)
	{
		VirtualMixer = &virtualMixer;
	}

	void ChannelView::SetMackieComposite(Mackie::MackieComposite& mackieComposite)
	{
		MackieComposite = &mackieComposite;
	}

	void ChannelView::SetInputChannelMute(int originId, int channel, bool on)
	{
		MackieComposite->SetChannelMute(channel, on);
	}

	void ChannelView::SetInputChannelSolo(int originId, int channel, bool on)
	{
		MackieComposite->SetChannelSolo(channel, on);
	}

	void ChannelView::OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		if (!on)
		{
			return;
		}

		auto channelWasMuted = ViewData.GetMute(channelId);
		ViewData.SetMute(channelId, !channelWasMuted);

		VirtualMixer->SetInputChannelMute(ViewData.GetId(), channelId, !channelWasMuted);
	}

	void ChannelView::OnChannelSoloPressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		if (!on)
		{
			return;
		}

		auto channelWasSolod = ViewData.GetSolo(channelId);
		ViewData.SetSolo(channelId, !channelWasSolod);

		VirtualMixer->SetInputChannelSolo(ViewData.GetId(), channelId, !channelWasSolod);
	}

	void ChannelView::OnBankForwardPressed()
	{
	}

	void ChannelView::OnBankBackwardsPressed()
	{
	}
}
