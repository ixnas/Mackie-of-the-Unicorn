//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_VIRTUALMIXER_H
#define MACKIE_OF_THE_UNICORN_VIRTUALMIXER_H

#include "Mixer.h"
#include <vector>
#include <memory>

namespace MackieOfTheUnicorn::Mixers
{
	class LinkedMixer;

	class VirtualMixer : public Mixer
	{
		std::vector<std::unique_ptr<LinkedMixer>> LinkedMixers;

	  public:
		explicit VirtualMixer(std::vector<std::unique_ptr<LinkedMixer>>& linkedMixers);
		void SetInputChannelMute(int originId, int channel, bool on) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_VIRTUALMIXER_H
