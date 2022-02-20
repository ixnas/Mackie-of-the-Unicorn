//
// Created by Sjoerd Scheffer on 20/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORYFAKE_H

#include "../../../../src/HTTP/Factories/HTTPDeviceFactory.h"
#include "../HTTPDeviceFake.h"

namespace MackieOfTheUnicorn::HTTP::Factories
{
	class HTTPDeviceFactoryFake : public HTTPDeviceFactory
	{
		std::unique_ptr<HTTPDevice> Create(std::string url) override
		{
			return std::make_unique<HTTP::HTTPDeviceFake>();
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_HTTPDEVICEFACTORYFAKE_H
