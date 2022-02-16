//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H

#include "../../../src/Mackie/MackieComposite.h"
#include <string>
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieCompositeFake : public MackieComposite
	{
	  public:
		std::optional<int> SetChannelMuteChannelId;
		std::optional<bool> SetChannelMuteOn;

		void OnChannelMutePressed(MackieDevice* origin, int channelId, bool on) override
		{
		}

		void SetChannelMute(int channelId, bool on) override
		{
			SetChannelMuteChannelId = channelId;
			SetChannelMuteOn = on;
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
