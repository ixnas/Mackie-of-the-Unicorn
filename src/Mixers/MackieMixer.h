//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEMIXER_H
#define MACKIE_OF_THE_UNICORN_MACKIEMIXER_H

namespace MackieOfTheUnicorn::Mixers
{
	/// Represents the
	class MackieMixer
	{
	  public:
		virtual ~MackieMixer() = default;

		/// Mutes or unmutes an input channel.
		virtual void SetChannelMute(int channelNumber, bool on) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEMIXER_H
