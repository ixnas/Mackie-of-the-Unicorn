//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LINKEDMIXER_H
#define MACKIE_OF_THE_UNICORN_LINKEDMIXER_H

#include "Mixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	class VirtualMixer;

	class LinkedMixer : public Mixer
	{
	  public:
		virtual void SetVirtualMixer(VirtualMixer* virtualMixer) = 0;
		virtual int GetId() = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_LINKEDMIXER_H
