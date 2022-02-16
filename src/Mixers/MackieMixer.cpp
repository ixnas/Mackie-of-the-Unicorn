//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#include "MackieMixer.h"
#include "../Mixers/VirtualMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	template<class OptionType>
	static bool OptionSet(std::vector<OptionType>& optionList, OptionType id)
	{
		return std::any_of(optionList.begin(), optionList.end(), [id](int i){ return i == id; });
	}

	template<class OptionType>
	static void SetOption(std::vector<OptionType>& optionList, OptionType id, bool on)
	{
		if (on)
		{
			if (OptionSet(optionList, id))
			{
				return;
			}

			optionList.push_back(id);
			return;
		}

		if (!OptionSet(optionList, id))
		{
			return;
		}

		optionList.erase(std::remove(optionList.begin(), optionList.end(), id), optionList.end());
	}

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
		if (!on)
		{
			return;
		}

		auto channelWasMuted = OptionSet(MutesOn, channelId);
		SetOption(MutesOn, channelId, !channelWasMuted);

		VirtualMixer->SetInputChannelMute(Id, channelId, !channelWasMuted);
		MackieComposite->SetChannelMute(channelId, !channelWasMuted);
	}
}
