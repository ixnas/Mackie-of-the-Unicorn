//
// Created by Sjoerd Scheffer on 04/03/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CHANNELVIEW_H
#define MACKIE_OF_THE_UNICORN_CHANNELVIEW_H

#include "MackieView.h"
#include "MackieViewData.h"

namespace MackieOfTheUnicorn::Views
{
	/// A view that shows the basic channel strips.
	class ChannelView : public MackieView
	{
		MackieViewData& ViewData;
		Mackie::MackieComposite* MackieComposite;
		Mixers::VirtualMixer* VirtualMixer;

	  public:
		explicit ChannelView(MackieViewData& viewData);
		void SetVirtualMixer(Mixers::VirtualMixer& virtualMixer) override;
		void SetMackieComposite(Mackie::MackieComposite& mackieComposite) override;
		void SetInputChannelMute(int originId, int channel, bool on) override;
		void SetInputChannelSolo(int originId, int channel, bool on) override;
		void OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on) override;
		void OnChannelSoloPressed(Mackie::MackieComposite* origin, int channelId, bool on) override;
		void OnBankForwardPressed() override;
		void OnBankBackwardsPressed() override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_CHANNELVIEW_H
