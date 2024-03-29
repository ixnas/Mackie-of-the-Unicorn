//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LINKEDMIXERFAKE_H
#define MACKIE_OF_THE_UNICORN_LINKEDMIXERFAKE_H

#include "../../../src/Mixers/LinkedMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	class LinkedMixerFake : public LinkedMixer
	{
	  public:
		int Id = 0;
		VirtualMixer* VirtualMixer = nullptr;

		std::optional<int> SetInputChannelMuteOriginId;
		std::optional<int> SetInputChannelMuteChannel;
		std::optional<bool> SetInputChannelMuteOn;

		std::optional<int> SetInputChannelSoloOriginId;
		std::optional<int> SetInputChannelSoloChannel;
		std::optional<bool> SetInputChannelSoloOn;

		std::optional<int> SetInputChannelLabelOriginId;
		std::optional<int> SetInputChannelLabelChannel;
		std::optional<std::string> SetInputChannelLabelLabel;

		int GetId() override
		{
			return Id;
		}

		void SetVirtualMixer(Mixers::VirtualMixer* virtualMixer) override
		{
			VirtualMixer = virtualMixer;
		}

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

#endif // MACKIE_OF_THE_UNICORN_LINKEDMIXERFAKE_H
