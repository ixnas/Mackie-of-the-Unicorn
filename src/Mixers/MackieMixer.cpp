//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "MackieMixer.h"
#include "../Mixers/VirtualMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	MackieMixer::MackieMixer(std::unique_ptr<Mackie::MackieComposite>& mackieComposite, int id) : MackieComposite(std::move(mackieComposite)), Id(id), VirtualMixer(nullptr)
	{
		MackieComposite->SetMackieListener(*this);
	}

	void MackieMixer::SetVirtualMixer(Mixers::VirtualMixer* virtualMixer)
	{
		VirtualMixer = virtualMixer;
	}

	int MackieMixer::GetId()
	{
		return Id;
	}

	void MackieMixer::SetInputChannelMute(int originId, int channel, bool on)
	{
		//SetOption(MutesOn, channel, on);
		ViewData.SetMute(channel, on);
		MackieComposite->SetChannelMute(channel, on);
	}

	void MackieMixer::OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		if (!on)
		{
			return;
		}

		auto channelWasMuted = ViewData.GetMute(channelId);
		//SetOption(MutesOn, channelId, !channelWasMuted);
		ViewData.SetMute(channelId, !channelWasMuted);

		VirtualMixer->SetInputChannelMute(Id, channelId, !channelWasMuted);
	}

	void MackieMixer::SetInputChannelSolo(int originId, int channel, bool on)
	{
		//SetOption(SolosOn, channel, on);
		ViewData.SetMute(channel, on);
		MackieComposite->SetChannelSolo(channel, on);
	}

	void MackieMixer::OnChannelSoloPressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		if (!on)
		{
			return;
		}

		auto channelWasSolod = ViewData.GetSolo(channelId);
		//SetOption(SolosOn, channelId, !channelWasSolod);
		ViewData.SetSolo(channelId, !channelWasSolod);

		VirtualMixer->SetInputChannelSolo(Id, channelId, !channelWasSolod);
	}
}
