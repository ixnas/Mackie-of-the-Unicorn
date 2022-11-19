//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MIXER_H
#define MACKIE_OF_THE_UNICORN_MIXER_H

namespace MackieOfTheUnicorn::Mixers
{
	/// Interface for all software and hardware mixers.
	class Mixer
	{
	  public:
		virtual ~Mixer() = default;

		/// Mutes a specified input channel.
		virtual void SetInputChannelMute(int originId, int channel, bool on) = 0;

		/// Solos a specified input channel.
		virtual void SetInputChannelSolo(int originId, int channel, bool on) = 0;

		/// Sets a label for a specified input channel.
		virtual void SetInputChannelLabel(int originId, int channel, std::string_view label) = 0;

		/// Sets the fader value for a specified input channel. Value should be linear between 0 and 1.
		virtual void SetInputChannelFader(int originId, int channel, double value) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MIXER_H
