//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_APPLICATION_H
#define MACKIE_OF_THE_UNICORN_APPLICATION_H

#include <map>
#include <memory>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieService;
}

namespace MackieOfTheUnicorn
{
	/// The main application controller.
	class Application
	{
		Mackie::MackieService* MackieService;

	  public:
		explicit Application(Mackie::MackieService& mackieService);
		std::map<int, std::string> GetAvailableInputDevices() const;
		std::map<int, std::string> GetAvailableOutputDevices() const;
	};
} // namespace MackieOfTheUnicorn

#endif // MACKIE_OF_THE_UNICORN_APPLICATION_H
