//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "MackieMixer.h"
#include "../Mixers/VirtualMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	MackieMixer::MackieMixer(std::unique_ptr<Mackie::MackieComposite>& mackieComposite, int id) : MackieComposite(std::move(mackieComposite)), Id(id), VirtualMixer(nullptr)
	{
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
		MackieComposite->SetChannelMute(channel, on);
	}

	void MackieMixer::OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on)
	{
		VirtualMixer->SetInputChannelMute(Id, channelId, on);
	}
}
