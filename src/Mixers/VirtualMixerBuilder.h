//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_VIRTUALMIXERBUILDER_H
#define MACKIE_OF_THE_UNICORN_VIRTUALMIXERBUILDER_H

#include "VirtualMixer.h"
#include "MackieMixer.h"
#include "../Mackie/MackieComposite.h"
#include "../HTTP/Factories/HTTPDeviceFactory.h"
#include "MOTUMixer.h"

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
		HTTP::Factories::HTTPDeviceFactory* HTTPDeviceFactory;
		std::unique_ptr<MackieMixer> MackieMixer;
		std::unique_ptr<Mixers::MOTUMixer> MOTUMixer;
		int CurrentMixerId;

	  public:
		explicit VirtualMixerBuilder(Mackie::MackieService& mackieService,
		                             HTTP::Factories::HTTPDeviceFactory& httpDeviceFactory);

		/// Adds a MackieMixer using sets of MIDI in and output port IDs.
		VirtualMixerBuilder* AddMackieMixer(std::vector<std::pair<int, int>>& inputAndOutputIds);

		// Adds a MOTUMixer using a URL.
		VirtualMixerBuilder* AddMOTUMixer(std::string hostname);

		/// Builds and returns a new VirtualMixer.
		std::unique_ptr<VirtualMixer> Build();
	};
}

#endif // MACKIE_OF_THE_UNICORN_VIRTUALMIXERBUILDER_H
