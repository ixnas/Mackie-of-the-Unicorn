//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H

#include "MackieService.h"

class MackieCompositeFactory;
class MackieDeviceFactory;
class MIDIService;

class MackieServiceImpl : public MackieService
{
	MackieCompositeFactory* MackieCompositeFactory;
	MackieDeviceFactory* MackieDeviceFactory;
	MIDIService* MIDIService;
  public:
	MackieServiceImpl(::MackieCompositeFactory& mackieCompositeFactory, ::MackieDeviceFactory& mackieDeviceFactory,
	                  ::MIDIService& midiService);
	std::map<int, std::string> GetDevices();
	std::unique_ptr<MackieComposite> GetMackieComposite(std::vector<int> deviceIds);
};

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H
