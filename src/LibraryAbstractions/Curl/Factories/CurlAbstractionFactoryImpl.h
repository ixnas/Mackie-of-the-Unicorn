//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORYIMPL_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORYIMPL_H

#include "CurlAbstractionFactory.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories
{
	class CurlAbstractionFactoryImpl : public CurlAbstractionFactory
	{
	  public:
		std::unique_ptr<Curl::CurlAbstraction> Create() override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORYIMPL_H
