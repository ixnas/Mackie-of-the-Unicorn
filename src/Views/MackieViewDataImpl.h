//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEVIEWDATAIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIEVIEWDATAIMPL_H

#include "MackieViewData.h"

namespace MackieOfTheUnicorn::Views
{
	class MackieViewDataImpl : public MackieViewData
	{
		int Id;
		std::vector<int> MutedChannels;
		std::vector<int> SolodChannels;
		std::map<int, std::string> ChannelLabels;
		std::map<int, double> ChannelFaders;

	  public:
		explicit MackieViewDataImpl(int id);
		int GetId() override;
		void SetMute(int channelId, bool on) override;
		bool GetMute(int channelId) override;
		void SetSolo(int channelId, bool on) override;
		bool GetSolo(int channelId) override;
		void SetLabel(int channelId, std::string_view label) override;
		std::string_view GetLabel(int channelId) override;
		void SetFader(int channelId, double value) override;
		double GetFader(int channelId) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEVIEWDATAIMPL_H
