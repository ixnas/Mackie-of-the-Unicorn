//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H

#include "MackieService.h"

class MackieServiceImpl : public MackieService
{
  public:
	std::map<int, std::string> GetDevices() override;
	std::unique_ptr<MackieComposite> GetMackieComposite(std::vector<int> deviceIds) override;
};

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICEIMPL_H
