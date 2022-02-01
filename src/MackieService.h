//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICE_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICE_H

#include <map>
#include <string>

class MackieComposite;

class MackieService
{
  public:
	virtual ~MackieService() = default;
	virtual std::map<int, std::string> GetDevices() = 0;
	virtual std::unique_ptr<MackieComposite> GetMackieComposite(std::vector<int> deviceIds) = 0;
};

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICE_H
