//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H

#include "../../../src/Mackie/MackieComposite.h"
#include "../../../src/Mackie/MackieDevice.h"

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

		std::optional<int> SetChannelTextChannel;
		std::optional<bool> SetChannelTextOnBottomRow;
		std::optional<std::string_view> SetChannelTextText;

		bool ScreenCleared = false;

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

		void SetChannelText(int channelNumber, bool onBottomRow, std::string_view text) override
		{
			SetChannelTextChannel = channelNumber;
			SetChannelTextOnBottomRow = onBottomRow;
			SetChannelTextText = text;
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

		void OnChannelFaderMoved(MackieDevice* origin, int channelId, double value) override
		{
		}

		void SetChannelFader(int channelNumber, double value) override
		{
		}

		void ClearScreen() override
		{
			ScreenCleared = true;
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
