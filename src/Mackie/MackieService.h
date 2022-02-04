//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICE_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICE_H

#include <map>
#include <string>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieComposite;

	class MackieService
	{
	  public:
		virtual ~MackieService() = default;
		virtual std::map<int, std::string> GetInputDevices() = 0;
		virtual std::map<int, std::string> GetOutputDevices() = 0;
		virtual std::unique_ptr<MackieComposite> GetMackieComposite(
		    const std::vector<std::pair<int, int>>& inAndOutIds) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICE_H
