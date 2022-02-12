//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LINKEDMIXERFAKE_H
#define MACKIE_OF_THE_UNICORN_LINKEDMIXERFAKE_H

#include "../../../src/Mixers/LinkedMixer.h"
#include <optional>

namespace MackieOfTheUnicorn::Mixers
{
	class LinkedMixerFake : public LinkedMixer
	{
	  public:
		int Id = 0;
		VirtualMixer* VirtualMixer = nullptr;

		std::optional<int> SetInputChannelMuteOriginId;
		std::optional<int> SetInputChannelChannel;
		std::optional<bool> SetInputChannelOn;

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
			SetInputChannelChannel = channel;
			SetInputChannelOn = on;
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_LINKEDMIXERFAKE_H
