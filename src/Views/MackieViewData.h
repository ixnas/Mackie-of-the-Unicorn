//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEVIEWDATA_H
#define MACKIE_OF_THE_UNICORN_MACKIEVIEWDATA_H

namespace MackieOfTheUnicorn::Views
{
	/// An object that stores state data that can be passed between MackieViews.
	class MackieViewData
	{
	  public:
		virtual ~MackieViewData() = default;

		/// Returns the current ID.
		virtual int GetId() = 0;

		/// Sets the mute for a channel.
		virtual void SetMute(int channelId, bool on) = 0;

		/// Returns whether the a channel is muted.
		virtual bool GetMute(int channelId) = 0;

		/// Sets the solo for a channel.
		virtual void SetSolo(int channelId, bool on) = 0;

		/// Returns whether the a channel is solo'd.
		virtual bool GetSolo(int channelId) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEVIEWDATA_H
