//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H

#include "../../../src/Mackie/MackieComposite.h"
#include "../../../src/Mackie/MackieDevice.h"
#include <string>
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieCompositeFake : public MackieComposite
	{
	  public:
		std::optional<int> SetChannelMuteChannelId;
		std::optional<bool> SetChannelMuteOn;
		std::vector<std::unique_ptr<MackieDevice>> MackieDevices;

		MackieCompositeFake() = default;

		explicit MackieCompositeFake(std::vector<std::unique_ptr<MackieDevice>>& mackieDevices) : MackieDevices(std::move(mackieDevices))
		{
		}

		void OnChannelMutePressed(MackieDevice* origin, int channelId, bool on) override
		{
		}

		void SetChannelMute(int channelId, bool on) override
		{
			SetChannelMuteChannelId = channelId;
			SetChannelMuteOn = on;
		}

		void SetMackieListener(MackieListener<MackieComposite>& mackieListener) override
		{
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
