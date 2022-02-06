//
// Created by Sjoerd Scheffer on 06/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_INVALIDARGUMENTEXCEPTION_H
#define MACKIE_OF_THE_UNICORN_INVALIDARGUMENTEXCEPTION_H

#include <stdexcept>

namespace MackieOfTheUnicorn::Exceptions
{
	class InvalidArgumentException : public std::runtime_error
	{
	};
} // namespace MackieOfTheUnicorn::Exceptions

#endif // MACKIE_OF_THE_UNICORN_INVALIDARGUMENTEXCEPTION_H
