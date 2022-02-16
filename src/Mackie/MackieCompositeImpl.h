//
// Created by Sjoerd Scheffer on 15/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEIMPL_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEIMPL_H

#include "MackieComposite.h"
#include <memory>
#include <vector>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieCompositeImpl : public MackieComposite
	{
		std::vector<std::unique_ptr<MackieDevice>> MackieDevices;

	  public:
		explicit MackieCompositeImpl(std::vector<std::unique_ptr<MackieDevice>>& mackieDevices);
		void SetChannelMute(int channelNumber, bool on) override;
		void OnChannelMutePressed(MackieDevice* origin, int channelId, bool on) override;
		void SetMackieListener(MackieListener<MackieComposite>& mackieListener) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEIMPL_H
