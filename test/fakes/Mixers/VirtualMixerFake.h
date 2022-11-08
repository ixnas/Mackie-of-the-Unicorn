//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_VIRTUALMIXERFAKE_H
#define MACKIE_OF_THE_UNICORN_VIRTUALMIXERFAKE_H

#include "../../../src/Mixers/VirtualMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	class VirtualMixerFake : public VirtualMixer
	{
	  public:
		std::optional<int> SetInputChannelMuteOriginId;
		std::optional<int> SetInputChannelMuteChannel;
		std::optional<bool> SetInputChannelMuteOn;

		std::optional<int> SetInputChannelSoloOriginId;
		std::optional<int> SetInputChannelSoloChannel;
		std::optional<bool> SetInputChannelSoloOn;

		std::optional<int> SetInputChannelLabelOriginId;
		std::optional<int> SetInputChannelLabelChannel;
		std::optional<std::string> SetInputChannelLabelLabel;

		void SetInputChannelMute(int originId, int channel, bool on) override
		{
			SetInputChannelMuteOriginId = originId;
			SetInputChannelMuteChannel = channel;
			SetInputChannelMuteOn = on;
		}

		void SetInputChannelSolo(int originId, int channel, bool on) override
		{
			SetInputChannelSoloOriginId = originId;
			SetInputChannelSoloChannel = channel;
			SetInputChannelSoloOn = on;
		}

		void SetInputChannelLabel(int originId, int channel, std::string_view label) override
		{
			SetInputChannelLabelOriginId = originId;
			SetInputChannelLabelChannel = channel;
			SetInputChannelLabelLabel = label;
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_VIRTUALMIXERFAKE_H
