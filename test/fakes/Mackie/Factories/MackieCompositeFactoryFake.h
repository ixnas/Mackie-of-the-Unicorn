//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYFAKE_H

#include "../../../../src/Mackie/Factories/MackieCompositeFactory.h"
#include "../MackieCompositeFake.h"

namespace MackieOfTheUnicorn::Mackie::Factories
{
	class MackieCompositeFactoryFake : public MackieCompositeFactory
	{
	  public:
		std::vector<std::pair<int, int>> DevicesArgument;

		std::unique_ptr<MackieComposite> Create(const std::vector<std::pair<int, int>>& devices) override
		{
			DevicesArgument = devices;
			return std::make_unique<MackieCompositeFake>();
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYFAKE_H
