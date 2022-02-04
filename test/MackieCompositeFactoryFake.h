//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYFAKE_H

#include "../src/MackieCompositeFactory.h"
#include "MackieCompositeFake.h"

class MackieCompositeFactoryFake : public MackieCompositeFactory
{
  public:
	std::unique_ptr<MackieComposite> Create(std::vector<std::unique_ptr<MackieDevice>> devices) override
	{
		auto instance = std::make_unique<MackieCompositeFake>();
		for (auto& device : devices)
			instance->AddMackieDevice(std::move(device));
		return instance;
	}
};

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORYFAKE_H
