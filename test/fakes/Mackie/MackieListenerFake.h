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
		MackieDevice* OnChannelMutePressedOrigin = nullptr;
		std::optional<int> OnChannelMutePressedChannelId;
		std::optional<bool> OnChannelMutePressedOn;

		void OnChannelMutePressed(T* origin, int channelId, bool on) override
		{
			OnChannelMutePressedOrigin = origin;
			OnChannelMutePressedChannelId = channelId;
			OnChannelMutePressedOn = on;
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIELISTENERFAKE_H
