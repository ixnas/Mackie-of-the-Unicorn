#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_APPLICATION_H
#define MACKIE_OF_THE_UNICORN_APPLICATION_H

#include <memory>

class MackieService;

class Application
{
	MackieService* MackieService;
  public:
	explicit Application(::MackieService& mackieService);
	std::string GetAvailableDevices() const;
};

#endif // MACKIE_OF_THE_UNICORN_APPLICATION_H
