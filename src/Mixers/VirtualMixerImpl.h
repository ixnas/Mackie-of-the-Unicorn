//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_VIRTUALMIXERIMPL_H
#define MACKIE_OF_THE_UNICORN_VIRTUALMIXERIMPL_H

#include "VirtualMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	class LinkedMixer;

	class VirtualMixerImpl : public VirtualMixer
	{
		std::vector<std::unique_ptr<LinkedMixer>> LinkedMixers;

	  public:
		explicit VirtualMixerImpl(std::vector<std::unique_ptr<LinkedMixer>>& linkedMixers);
		void SetInputChannelMute(int originId, int channel, bool on) override;
		void SetInputChannelSolo(int originId, int channel, bool on) override;
		void SetInputChannelLabel(int originId, int channel, std::string_view label) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_VIRTUALMIXERIMPL_H
