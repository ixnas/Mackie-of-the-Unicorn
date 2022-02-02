//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICE_H

#include <string>

class MackieDevice
{
  public:
	virtual ~MackieDevice() = default;
	virtual void SetText(int position, std::string text) = 0;
};

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICE_H
