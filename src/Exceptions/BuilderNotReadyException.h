//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_BUILDERNOTREADYEXCEPTION_H
#define MACKIE_OF_THE_UNICORN_BUILDERNOTREADYEXCEPTION_H

#include <stdexcept>

namespace MackieOfTheUnicorn::Exceptions
{
	class BuilderNotReadyException : public std::runtime_error
	{
	  public:
		explicit BuilderNotReadyException(const std::string& message) : runtime_error(message)
		{
		}
	};
} // namespace MackieOfTheUnicorn::Exceptions

#endif // MACKIE_OF_THE_UNICORN_BUILDERNOTREADYEXCEPTION_H
