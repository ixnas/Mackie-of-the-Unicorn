//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MOTUMIXER_H
#define MACKIE_OF_THE_UNICORN_MOTUMIXER_H

#include "LinkedMixer.h"
#include "../HTTP/HTTPDevice.h"
#include "../HTTP/HTTPListener.h"

namespace MackieOfTheUnicorn::HTTP::Factories
{
	class HTTPDeviceFactory;
}

namespace MackieOfTheUnicorn::Mixers
{
	/// A LinkedMixer implementation that represents a MOTU DSP mixer.
	class MOTUMixer : public LinkedMixer, public HTTP::HTTPListener
	{
		std::unique_ptr<HTTP::HTTPDevice> HTTPDevice;
		VirtualMixer* VirtualMixer;
		int Id;

	  public:
		explicit MOTUMixer(std::unique_ptr<HTTP::HTTPDevice> httpDevice, int id);
		void SetVirtualMixer(Mixers::VirtualMixer* virtualMixer) override;
		int GetId() override;
		void SetInputChannelMute(int originId, int channel, bool on) override;
		void SetInputChannelSolo(int originId, int channel, bool on) override;
		void HTTPCallback(std::pair<std::string, JSON::JSONValue>& message) override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MOTUMIXER_H
