//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORY_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORY_H

#include "../CurlAbstraction.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories
{
	class CurlAbstractionFactory
	{
	  public:
		virtual ~CurlAbstractionFactory() = default;
		virtual std::unique_ptr<Curl::CurlAbstraction> Create() = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORY_H
