//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICEFAKE_H

#include "../../../src/Mackie/MackieService.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieServiceFake : public MackieService
	{
	  public:
		std::map<int, std::string> GetInputDevices() override
		{
			return {{0, "in1"}, {1, "in2"}};
		}

		std::map<int, std::string> GetOutputDevices() override
		{
			return {{0, "out1"}, {1, "out2"}};
		}

		std::unique_ptr<MackieComposite> GetMackieComposite(
		    const std::vector<std::pair<int, int>>& inAndOutIds) override
		{
			return {};
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICEFAKE_H
