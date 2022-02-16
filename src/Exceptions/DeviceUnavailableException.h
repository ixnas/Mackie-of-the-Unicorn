//
// Created by Sjoerd Scheffer on 06/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_DEVICEUNAVAILABLEEXCEPTION_H
#define MACKIE_OF_THE_UNICORN_DEVICEUNAVAILABLEEXCEPTION_H

#include <stdexcept>

namespace MackieOfTheUnicorn::Exceptions
{
	class DeviceUnavailableException : public std::runtime_error
	{
	  public:
		explicit DeviceUnavailableException(const std::string& message) : runtime_error(message)
		{
		}
	};
} // namespace MackieOfTheUnicorn::Exceptions

#endif // MACKIE_OF_THE_UNICORN_DEVICEUNAVAILABLEEXCEPTION_H
