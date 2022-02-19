//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORYFAKE_H

#include "../../../../src/LibraryAbstractions/Curl/Factories/CurlAbstractionFactory.h"
#include "../CurlAbstractionFake.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories
{
	class CurlAbstractionFactoryFake : public CurlAbstractionFactory
	{
	  public:
		std::vector<Curl::CurlAbstractionFake*> CreateCurlAbstractionFakes;

		std::unique_ptr<Curl::CurlAbstraction> Create() override
		{
			auto instance = std::make_unique<Curl::CurlAbstractionFake>();
			CreateCurlAbstractionFakes.push_back(instance.get());
			return instance;
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_CURLABSTRACTIONFACTORYFAKE_H
