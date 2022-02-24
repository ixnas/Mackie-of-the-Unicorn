//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIELISTENERFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIELISTENERFAKE_H

#include "../../../src/Mackie/MackieListener.h"
#include <optional>

namespace MackieOfTheUnicorn::Mackie
{
	template<class T>
	class MackieListenerFake : public MackieListener<T>
	{
	  public:
		T* OnChannelMutePressedOrigin = nullptr;
		std::optional<int> OnChannelMutePressedChannelId;
		std::optional<bool> OnChannelMutePressedOn;

		T* OnChannelSoloPressedOrigin = nullptr;
		std::optional<int> OnChannelSoloPressedChannelId;
		std::optional<bool> OnChannelSoloPressedOn;

		void OnChannelMutePressed(T* origin, int channelId, bool on) override
		{
			OnChannelMutePressedOrigin = origin;
			OnChannelMutePressedChannelId = channelId;
			OnChannelMutePressedOn = on;
		}

		void OnChannelSoloPressed(T* origin, int channelId, bool on) override
		{
			OnChannelSoloPressedOrigin = origin;
			OnChannelSoloPressedChannelId = channelId;
			OnChannelSoloPressedOn = on;
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIELISTENERFAKE_H
