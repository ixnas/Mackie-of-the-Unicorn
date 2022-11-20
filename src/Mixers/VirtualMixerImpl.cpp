//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "VirtualMixerImpl.h"
#include "LinkedMixer.h"

namespace MackieOfTheUnicorn::Mixers
{
	VirtualMixerImpl::VirtualMixerImpl(std::vector<std::unique_ptr<LinkedMixer>>& linkedMixers)
	    : LinkedMixers(std::move(linkedMixers))
	{
		for (const auto& linkedMixer : LinkedMixers)
		{
			linkedMixer->SetVirtualMixer(this);
		}
	}

	void VirtualMixerImpl::SetInputChannelMute(int originId, int channel, bool on)
	{
		SetOnLinkedMixers(originId, [=](auto originId, auto& linkedMixer) {
			linkedMixer.SetInputChannelMute(originId, channel, on);
		});
	}

	void VirtualMixerImpl::SetInputChannelSolo(int originId, int channel, bool on)
	{
		SetOnLinkedMixers(originId, [=](auto originId, auto& linkedMixer) {
			linkedMixer.SetInputChannelSolo(originId, channel, on);
		});
	}

	void VirtualMixerImpl::SetInputChannelLabel(int originId, int channel, std::string_view label)
	{
		SetOnLinkedMixers(originId, [=](auto originId, auto& linkedMixer) {
			linkedMixer.SetInputChannelLabel(originId, channel, label);
		});
	}

	void VirtualMixerImpl::SetInputChannelFader(int originId, int channel, double value)
	{
		SetOnLinkedMixers(originId, [=](auto originId, auto& linkedMixer) {
			linkedMixer.SetInputChannelFader(originId, channel, value);
		});
	}

	void VirtualMixerImpl::SetOnLinkedMixers(int originId, std::function<void(int, LinkedMixer&)> const& setterFunction)
	{
		for (const auto& linkedMixer : LinkedMixers)
		{
			if (linkedMixer->GetId() == originId)
			{
				continue;
			}

			setterFunction(originId, *linkedMixer);
		}
	}
} // namespace MackieOfTheUnicorn::Mixers