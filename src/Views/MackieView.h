//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEVIEW_H
#define MACKIE_OF_THE_UNICORN_MACKIEVIEW_H

#include "../Mixers/VirtualMixer.h"
#include "../Mackie/MackieListener.h"
#include "../Mackie/MackieComposite.h"

namespace MackieOfTheUnicorn::Views
{
	/// Provides an interface for classes that represent a view for a MackieMixer.
	class MackieView : public Mixers::Mixer, public Mackie::MackieListener<Mackie::MackieComposite>
	{
	  public:
		/// Sets the VirtualMixer instance.
		virtual void SetVirtualMixer(Mixers::VirtualMixer& virtualMixer) = 0;

		/// Sets the MackieComposite instance.
		virtual void SetMackieComposite(Mackie::MackieComposite& mackieComposite) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEVIEW_H
