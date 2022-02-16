//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYIMPL_H

#include "MackieCompositeFactory.h"
#include "MackieDeviceFactory.h"
#include "../MackieComposite.h"

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIService;
}

namespace MackieOfTheUnicorn::Mackie::Factories
{
	class MackieCompositeFactoryImpl : public MackieCompositeFactory
	{
		MIDI::MIDIService* MIDIService;
		MackieDeviceFactory* MackieDeviceFactory;

	  public:
		explicit MackieCompositeFactoryImpl(MIDI::MIDIService& midiService, Factories::MackieDeviceFactory& mackieDeviceFactory);
		std::unique_ptr<MackieComposite> Create(const std::vector<std::pair<int, int>>& inputAndOutputIds) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYIMPL_H
