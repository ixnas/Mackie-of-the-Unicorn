//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORY_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORY_H

#include <memory>

class MackieComposite;

class MackieCompositeFactory
{
  public:
	virtual ~MackieCompositeFactory() = default;
	virtual std::unique_ptr<MackieComposite> Create(std::vector<std::unique_ptr<MackieDevice>> devices) = 0;
};

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORY_H
