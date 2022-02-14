//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEINTERFACE_H
#define MACKIE_OF_THE_UNICORN_MACKIEINTERFACE_H

namespace MackieOfTheUnicorn::Mackie
{
	/// Provides an interface for MackieComposite and MackieDevice components.
	class MackieInterface
	{
	  public:
		virtual ~MackieInterface() = default;

		/// Mutes or unmutes an input channel.
		virtual void SetChannelMute(int channelNumber, bool on) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEINTERFACE_H
