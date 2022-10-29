//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEIMPL_H

#include "MackieComposite.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieCompositeImpl : public MackieComposite
	{
		std::vector<std::unique_ptr<MackieDevice>> MackieDevices;
		MackieListener<MackieComposite>* MackieListener;

	  public:
		explicit MackieCompositeImpl(std::vector<std::unique_ptr<MackieDevice>>& mackieDevices);
		void SetChannelMute(int channelNumber, bool on) override;
		void OnChannelMutePressed(MackieDevice* origin, int channelId, bool on) override;
		void SetChannelSolo(int channelNumber, bool on) override;
		void OnChannelSoloPressed(MackieDevice* origin, int channelId, bool on) override;
		void SetChannelText(int channelNumber, bool onBottomRow, std::string_view text) override;
		void OnBankForwardPressed() override;
		void OnBankBackwardsPressed() override;
		void SetMackieListener(Mackie::MackieListener<MackieComposite>& mackieListener) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEIMPL_H
