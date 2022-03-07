//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICE_H

#include "MackieInterface.h"
#include "MackieListener.h"
#include "../MIDI/MIDIReceiver.h"

namespace MackieOfTheUnicorn::Mackie
{
	/// Provides an interface to communicate with a Mackie controller.
	class MackieDevice : public MackieInterface, public MIDI::MIDIReceiver
	{
	  public:
		/// Sets a MackieListener for state changes (typically a MackieComposite).
		virtual void SetMackieListener(MackieListener<MackieDevice>& mackieListener) = 0;
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICE_H
