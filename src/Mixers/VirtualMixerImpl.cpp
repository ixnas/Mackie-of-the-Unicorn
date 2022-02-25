//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "VirtualMixerImpl.h"
#include "LinkedMixer.h"
#include <utility>

namespace MackieOfTheUnicorn::Mixers
{
	VirtualMixerImpl::VirtualMixerImpl(std::vector<std::unique_ptr<LinkedMixer>>& linkedMixers) : LinkedMixers(std::move(linkedMixers))
	{
		for (const auto& linkedMixer : LinkedMixers)
		{
			linkedMixer->SetVirtualMixer(this);
		}
	}

	void VirtualMixerImpl::SetInputChannelMute(int originId, int channel, bool on)
	{
		for(const auto& linkedMixer : LinkedMixers)
		{
			if (linkedMixer->GetId() == originId)
			{
				continue;
			}

			linkedMixer->SetInputChannelMute(originId, channel, on);
		}
	}

	void VirtualMixerImpl::SetInputChannelSolo(int originId, int channel, bool on)
	{
		for(const auto& linkedMixer : LinkedMixers)
		{
			if (linkedMixer->GetId() == originId)
			{
				continue;
			}

			linkedMixer->SetInputChannelSolo(originId, channel, on);
		}
	}
}