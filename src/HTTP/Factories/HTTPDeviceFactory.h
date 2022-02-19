//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORY_H
#define MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORY_H

#include "../HTTPDevice.h"

namespace MackieOfTheUnicorn::HTTP::Factories
{
	class HTTPDeviceFactory
	{
	  public:
		virtual ~HTTPDeviceFactory() = default;
		virtual std::unique_ptr<HTTPDevice> Create(std::string url) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORY_H
