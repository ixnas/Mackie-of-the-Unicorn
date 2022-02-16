//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H

#include "MackieListener.h"
#include "MackieInterface.h"
#include "MackieDevice.h"
#include <string>

namespace MackieOfTheUnicorn::Mackie
{
	/// Provides an interface to communicate with a group of Mackie controllers.
	class MackieComposite : public MackieListener<MackieDevice>, public MackieInterface
	{
	  public:
		/// Sets a MackieListener for state changes (typically a MackieMixer).
		virtual void SetMackieListener(MackieListener<MackieComposite>& mackieListener) = 0;
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
