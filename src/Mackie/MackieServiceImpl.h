//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H

#include "MackieService.h"

namespace MackieOfTheUnicorn::Mackie::Factories
{
	class MackieCompositeFactory;
	class MackieDeviceFactory;
}

namespace MackieOfTheUnicorn::MIDI
{
	class MIDIService;
}

namespace MackieOfTheUnicorn::Mackie
{
	class MackieServiceImpl : public MackieService
	{
		Factories::MackieCompositeFactory* MackieCompositeFactory;
		Factories::MackieDeviceFactory* MackieDeviceFactory;
		MIDI::MIDIService* MIDIService;

	  public:
		MackieServiceImpl(Factories::MackieCompositeFactory& mackieCompositeFactory, Factories::MackieDeviceFactory& mackieDeviceFactory,
		                  MIDI::MIDIService& midiService);
		std::map<int, std::string> GetInputDevices() override;
		std::map<int, std::string> GetOutputDevices() override;
		std::unique_ptr<MackieComposite> GetMackieComposite(const std::vector<std::pair<int, int>>& inAndOutputIds) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H
