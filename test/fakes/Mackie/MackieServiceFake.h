//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICEFAKE_H

#include "../../../src/Mackie/MackieService.h"
#include "MackieCompositeFake.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieServiceFake : public MackieService
	{
	  public:
		std::map<int, std::string> InputDevices;
		std::map<int, std::string> OutputDevices;

		std::map<int, std::string> GetInputDevices() override
		{
			return InputDevices;
		}

		std::map<int, std::string> GetOutputDevices() override
		{
			return OutputDevices;
		}

		std::unique_ptr<MackieComposite> GetMackieComposite(
		    const std::vector<std::pair<int, int>>& inAndOutIds) override
		{
			return std::make_unique<MackieCompositeFake>();
		}
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICEFAKE_H
