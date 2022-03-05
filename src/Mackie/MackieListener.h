//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIELISTENER_H
#define MACKIE_OF_THE_UNICORN_MACKIELISTENER_H

namespace MackieOfTheUnicorn::Mackie
{
	/// @brief Interface for classes that listen to state changes from a MackieDevice.
	/// @tparam OriginType The type of the object that the implementation listens to.
	template<class OriginType>
	class MackieListener
	{
	  public:
		virtual ~MackieListener() = default;

		/// Handles an event where a MackieDevice changes a channel mute.
		virtual void OnChannelMutePressed(OriginType* origin, int channelId, bool on) = 0;

		/// Handles an event where a MackieDevice changes a channel solo.
		virtual void OnChannelSoloPressed(OriginType* origin, int channelId, bool on) = 0;

		/// Handles an event where a MackieDevice banks to the next 8 channels.
		virtual void OnBankForwardPressed() = 0;

		/// Handles an event where a MackieDevice banks to the previous 8 channels.
		virtual void OnBankBackwardsPressed() = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIELISTENER_H
