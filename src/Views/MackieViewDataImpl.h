//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEVIEWDATAIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIEVIEWDATAIMPL_H

#include "MackieViewData.h"
#include <vector>

namespace MackieOfTheUnicorn::Views
{
	class MackieViewDataImpl : public MackieViewData
	{
		std::vector<int> MutedChannels;
		std::vector<int> SolodChannels;

	  public:
		void SetMute(int channelId, bool on) override;
		bool GetMute(int channelId) override;
		void SetSolo(int channelId, bool on) override;
		bool GetSolo(int channelId) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEVIEWDATAIMPL_H
