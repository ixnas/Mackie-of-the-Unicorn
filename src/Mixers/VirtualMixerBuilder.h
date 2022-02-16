//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_VIRTUALMIXERBUILDER_H
#define MACKIE_OF_THE_UNICORN_VIRTUALMIXERBUILDER_H

#include <vector>
#include <memory>
#include "VirtualMixer.h"
#include "MackieMixer.h"
#include "../Mackie/MackieComposite.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieService;
}

namespace MackieOfTheUnicorn::Mixers
{
	/// Builds VirtualMixers with LinkedMixers.
	class VirtualMixerBuilder
	{
		Mackie::MackieService* MackieService;
		std::unique_ptr<MackieMixer> MackieMixer;
		int CurrentMixerId;

	  public:
		explicit VirtualMixerBuilder(Mackie::MackieService& mackieService);

		/// Adds a MackieMixer using sets of MIDI in and output port IDs.
		VirtualMixerBuilder* AddMackieMixer(std::vector<std::pair<int, int>>& inputAndOutputIds);

		/// Builds and returns a new VirtualMixer.
		std::unique_ptr<VirtualMixer> Build();
	};
}

#endif // MACKIE_OF_THE_UNICORN_VIRTUALMIXERBUILDER_H
