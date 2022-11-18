//
// Created by Sjoerd Scheffer on 04/03/2022.
//

#include "ChannelView.h"

namespace MackieOfTheUnicorn::Views
{
	static void OnChangeOffset(int previousOffset, int nextOffset, MackieViewData& viewData, Mackie::MackieComposite& mackieComposite)
	{
		for (auto i = previousOffset; i < 48; i++)
		{
			auto currentMute = viewData.GetMute(i);
			auto nextMute = viewData.GetMute(i + nextOffset - previousOffset);

			if (currentMute != nextMute)
			{
				mackieComposite.SetChannelMute(i - previousOffset, nextMute);
			}

			auto currentSolo = viewData.GetSolo(i);
			auto nextSolo = viewData.GetSolo(i + nextOffset - previousOffset);

			if (currentSolo != nextSolo)
			{
				mackieComposite.SetChannelSolo(i - previousOffset, nextSolo);
			}

			auto currentLabel = viewData.GetLabel(i);
			auto nextLabel = viewData.GetLabel(i + nextOffset - previousOffset);

			if (currentLabel != nextLabel)
			{
				mackieComposite.SetChannelText(i - previousOffset, false, nextLabel);
			}
		}
	}

	ChannelView::ChannelView(MackieViewData& viewData) : ViewData(viewData), MackieComposite(nullptr), VirtualMixer(nullptr), Offset(0)
	{
	}

	void ChannelView::SetVirtualMixer(Mixers::VirtualMixer& virtualMixer)
	{
		VirtualMixer = &virtualMixer;
	}

	void ChannelView::SetMackieComposite(Mackie::MackieComposite& mackieComposite)
	{
		MackieComposite = &mackieComposite;
		MackieComposite->ClearScreen();
	}

	void ChannelView::SetInputChannelMute(int originId, int channel, bool on)
	{
		MackieComposite->SetChannelMute(channel - Offset, on);
	}

	void ChannelView::SetInputChannelSolo(int originId, int channel, bool on)
	{
		MackieComposite->SetChannelSolo(channel - Offset, on);
	}

	void ChannelView::OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		if (!on)
		{
			return;
		}

		channelId = channelId + Offset;

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

		channelId = channelId + Offset;

		auto channelWasSolod = ViewData.GetSolo(channelId);
		ViewData.SetSolo(channelId, !channelWasSolod);

		VirtualMixer->SetInputChannelSolo(ViewData.GetId(), channelId, !channelWasSolod);
	}

	void ChannelView::OnBankForwardPressed()
	{
		if (Offset >= 40)
		{
			return;
		}

		auto previousOffset = Offset;
		auto nextOffset = previousOffset + 8;

		OnChangeOffset(previousOffset, nextOffset, ViewData, *MackieComposite);

		Offset = nextOffset;
	}

	void ChannelView::OnBankBackwardsPressed()
	{
		if (Offset <= 0)
		{
			return;
		}

		auto previousOffset = Offset;
		auto nextOffset = previousOffset - 8;

		OnChangeOffset(previousOffset, nextOffset, ViewData, *MackieComposite);

		Offset = nextOffset;
	}

	void ChannelView::SetInputChannelLabel(int originId, int channel, std::string_view label)
	{
		MackieComposite->SetChannelText(channel - Offset, false, label);
	}

	void ChannelView::OnChannelFaderMoved(Mackie::MackieComposite* origin, int channelId, double value)
	{
	}
}
