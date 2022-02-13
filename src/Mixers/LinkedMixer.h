//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LINKEDMIXER_H
#define MACKIE_OF_THE_UNICORN_LINKEDMIXER_H

#include "Mixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	class VirtualMixer;

	/// Represents a hardware mixer that the VirtualMixer can manage.
	class LinkedMixer : public Mixer
	{
	  public:
		/// Sets the VirtualMixer instance that the LinkedMixer will update.
		virtual void SetVirtualMixer(VirtualMixer* virtualMixer) = 0;

		/// Returns a unique ID number for this mixer.
		virtual int GetId() = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_LINKEDMIXER_H
