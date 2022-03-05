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
		std::optional<int> SetChannelSoloChannelId;
		std::optional<bool> SetChannelSoloOn;
		std::vector<std::unique_ptr<MackieDevice>> MackieDevices;

		std::vector<bool> SolosOn;
		std::vector<int> SoloChannels;
		std::vector<bool> MutesOn;
		std::vector<int> MuteChannels;

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
			MuteChannels.push_back(channelId);
			MutesOn.push_back(on);
		}

		void OnChannelSoloPressed(MackieDevice* origin, int channelId, bool on) override
		{
		}

		void SetChannelSolo(int channelId, bool on) override
		{
			SetChannelSoloChannelId = channelId;
			SetChannelSoloOn = on;
			SoloChannels.push_back(channelId);
			SolosOn.push_back(on);
		}

		void SetMackieListener(MackieListener<MackieComposite>& mackieListener) override
		{
		}

		void OnBankForwardPressed() override
		{

		}

		void OnBankBackwardsPressed() override
		{

		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
