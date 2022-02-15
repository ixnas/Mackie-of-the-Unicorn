//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIELISTENER_H
#define MACKIE_OF_THE_UNICORN_MACKIELISTENER_H

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;

	/// Interface for classes that listen to state changes from a MackieDevice.
	class MackieListener
	{
	  public:
		virtual ~MackieListener() = default;

		/// Handles an event where a MackieDevice changes a channel mute.
		virtual void OnSetChannelMute(MackieDevice* origin, int channelId, bool on) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIELISTENER_H