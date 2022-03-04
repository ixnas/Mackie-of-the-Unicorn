//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#include "MackieViewDataImpl.h"

namespace MackieOfTheUnicorn::Views
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
			optionList.push_back(id);
			return;
		}

		optionList.erase(std::remove(optionList.begin(), optionList.end(), id), optionList.end());
	}

	int MackieViewDataImpl::GetId()
	{
		return Id;
	}

	void MackieViewDataImpl::SetMute(int channelId, bool on)
	{
		SetOption(MutedChannels, channelId, on);
	}

	bool MackieViewDataImpl::GetMute(int channelId)
	{
		return OptionSet(MutedChannels, channelId);
	}

	void MackieViewDataImpl::SetSolo(int channelId, bool on)
	{
		SetOption(SolodChannels, channelId, on);
	}

	bool MackieViewDataImpl::GetSolo(int channelId)
	{
		return OptionSet(SolodChannels, channelId);
	}

	MackieViewDataImpl::MackieViewDataImpl(int id) : Id(id)
	{
	}
}
