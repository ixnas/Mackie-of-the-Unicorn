//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEMIXER_H
#define MACKIE_OF_THE_UNICORN_MACKIEMIXER_H

#include "LinkedMixer.h"
#include "../Mackie/MackieComposite.h"
#include "../Views/MackieViewDataImpl.h"
#include "../StateMachine.h"
#include "../Views/MackieView.h"
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;
}

namespace MackieOfTheUnicorn::Mixers
{
	/// A LinkedMixer implementation that represents a Mackie control surface.
	class MackieMixer
	    : public LinkedMixer,
	      public Mackie::MackieListener<Mackie::MackieComposite>,
	      public StateMachine<Views::MackieView, VirtualMixer&, Mackie::MackieComposite&>
	{
		std::unique_ptr<Mackie::MackieComposite> MackieComposite;
		VirtualMixer* VirtualMixer;
		Views::MackieViewDataImpl ViewData;
		std::unique_ptr<Views::MackieView> View;

	  public:
		explicit MackieMixer(std::unique_ptr<Mackie::MackieComposite>& mackieComposite, int id);
		void SetVirtualMixer(Mixers::VirtualMixer* virtualMixer) override;
		int GetId() override;
		void SetInputChannelMute(int originId, int channel, bool on) override;
		void OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on) override;
		void SetInputChannelSolo(int originId, int channel, bool on) override;
		void OnChannelSoloPressed(Mackie::MackieComposite* origin, int channelId, bool on) override;
		void OnBankForwardPressed() override;
		void OnBankBackwardsPressed() override;
		void SetState(std::unique_ptr<Views::MackieView> newState, Mixers::VirtualMixer& virtualMixer, Mackie::MackieComposite& mackieComposite) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEMIXER_H
