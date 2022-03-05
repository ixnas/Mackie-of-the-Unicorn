//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "MackieMixer.h"
#include "../Views/ChannelView.h"

namespace MackieOfTheUnicorn::Mixers
{
	MackieMixer::MackieMixer(std::unique_ptr<Mackie::MackieComposite>& mackieComposite, int id) : MackieComposite(std::move(mackieComposite)), VirtualMixer(nullptr), ViewData(id)
	{
		MackieComposite->SetMackieListener(*this);
		View = std::make_unique<Views::ChannelView>(ViewData);
		View->SetMackieComposite(*MackieComposite);
	}

	void MackieMixer::SetVirtualMixer(Mixers::VirtualMixer* virtualMixer)
	{
		VirtualMixer = virtualMixer;
		View->SetVirtualMixer(*virtualMixer);
	}

	int MackieMixer::GetId()
	{
		return ViewData.GetId();
	}

	void MackieMixer::SetInputChannelMute(int originId, int channel, bool on)
	{
		ViewData.SetMute(channel, on);
		View->SetInputChannelMute(originId, channel, on);
	}

	void MackieMixer::OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		View->OnChannelMutePressed(origin, channelId, on);
	}

	void MackieMixer::SetInputChannelSolo(int originId, int channel, bool on)
	{
		ViewData.SetMute(channel, on);
		View->SetInputChannelSolo(originId, channel, on);
	}

	void MackieMixer::OnChannelSoloPressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		View->OnChannelSoloPressed(origin, channelId, on);
	}

	void MackieMixer::OnBankForwardPressed()
	{
	}

	void MackieMixer::OnBankBackwardsPressed()
	{
	}

	void MackieMixer::SetState(std::unique_ptr<Views::MackieView> newState, Mixers::VirtualMixer& virtualMixer,
	                           Mackie::MackieComposite& mackieComposite)
	{
	}
}
