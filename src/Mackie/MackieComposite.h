//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H

#include "MackieListener.h"
#include "MackieInterface.h"
#include <string>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;

	/// Provides an interface to communicate with a group of Mackie controllers.
	class MackieComposite : public MackieListener<MackieDevice>, public MackieInterface
	{
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
