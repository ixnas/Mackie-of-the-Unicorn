//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_VIRTUALMIXERIMPL_H
#define MACKIE_OF_THE_UNICORN_VIRTUALMIXERIMPL_H

#include "VirtualMixer.h"
#include <vector>
#include <memory>

namespace MackieOfTheUnicorn::Mixers
{
	class LinkedMixer;

	/// Manages the state and communication between all real mixers.
	class VirtualMixerImpl : public VirtualMixer
	{
		std::vector<std::unique_ptr<LinkedMixer>> LinkedMixers;

	  public:
		explicit VirtualMixerImpl(std::vector<std::unique_ptr<LinkedMixer>>& linkedMixers);
		void SetInputChannelMute(int originId, int channel, bool on) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_VIRTUALMIXERIMPL_H
