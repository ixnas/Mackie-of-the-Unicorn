//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEMIXER_H
#define MACKIE_OF_THE_UNICORN_MACKIEMIXER_H

#include "LinkedMixer.h"
#include "../Mackie/MackieComposite.h"
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;
}

namespace MackieOfTheUnicorn::Mixers
{
	/// A LinkedMixer implementation that represents a Mackie control surface.
	class MackieMixer : public LinkedMixer, public Mackie::MackieListener<Mackie::MackieComposite>
	{
		std::unique_ptr<Mackie::MackieComposite> MackieComposite;
		VirtualMixer* VirtualMixer;
		int Id;
		std::vector<int> MutesOn;

	  public:
		explicit MackieMixer(std::unique_ptr<Mackie::MackieComposite>& mackieComposite, int id);
		void SetVirtualMixer(Mixers::VirtualMixer* virtualMixer) override;
		int GetId() override;
		void SetInputChannelMute(int originId, int channel, bool on) override;
		void OnChannelMutePressed(Mackie::MackieComposite* origin, int channelId, bool on) override;
		void SetInputChannelSolo(int originId, int channel, bool on) override;
		void OnChannelSoloPressed(Mackie::MackieComposite* origin, int channelId, bool on) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEMIXER_H
