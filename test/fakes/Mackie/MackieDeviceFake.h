//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H

#include "../../../src/Mackie/MackieDevice.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDeviceFake : public MackieDevice
	{
	  public:
		MackieListener<MackieDevice>* MackieListener;
		std::optional<int> SetChannelMuteChannelNumber;
		std::optional<int> SetChannelMuteOn;

		std::optional<int> SetChannelSoloChannelNumber;
		std::optional<int> SetChannelSoloOn;

		std::optional<int> SetChannelTextChannelNumber;
		std::optional<bool> SetChannelTextOnBottomRow;
		std::optional<std::string_view> SetChannelTextText;

		bool ScreenCleared = false;

		void SetMackieListener(Mackie::MackieListener<MackieDevice>& mackieListener) override
		{
			MackieListener = &mackieListener;
		}

		void SetChannelMute(int channelNumber, bool on) override
		{
			SetChannelMuteChannelNumber = channelNumber;
			SetChannelMuteOn = on;
		}

		void SetChannelSolo(int channelNumber, bool on) override
		{
			SetChannelSoloChannelNumber = channelNumber;
			SetChannelSoloOn = on;
		}

		void SetChannelText(int channelNumber, bool onBottomRow, std::string_view text) override
		{
			SetChannelTextChannelNumber = channelNumber;
			SetChannelTextOnBottomRow = onBottomRow;
			SetChannelTextText = text;
		}

		void OnChannelMutePressed(int channelNumber, bool on)
		{
			MackieListener->OnChannelMutePressed(this, channelNumber, on);
		}

		void OnChannelSoloPressed(int channelNumber, bool on)
		{
			MackieListener->OnChannelSoloPressed(this, channelNumber, on);
		}

		void MIDICallback(std::vector<unsigned char>& message) override
		{
		}

		void ClearScreen() override
		{
			ScreenCleared = true;
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
