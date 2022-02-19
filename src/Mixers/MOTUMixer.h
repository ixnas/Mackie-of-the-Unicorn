//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MOTUMIXER_H
#define MACKIE_OF_THE_UNICORN_MOTUMIXER_H

#include "LinkedMixer.h"
#include "../HTTP/HTTPDevice.h"

namespace MackieOfTheUnicorn::HTTP::Factories
{
	class HTTPDeviceFactory;
}

namespace MackieOfTheUnicorn::Mixers
{
	class MOTUMixer : public LinkedMixer
	{
		std::unique_ptr<HTTP::HTTPDevice> HTTPDevice;
		VirtualMixer* VirtualMixer;

	  public:
		explicit MOTUMixer(std::unique_ptr<HTTP::HTTPDevice> httpDevice);
		void SetVirtualMixer(Mixers::VirtualMixer* virtualMixer) override;
		int GetId() override;
		void SetInputChannelMute(int originId, int channel, bool on) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MOTUMIXER_H
