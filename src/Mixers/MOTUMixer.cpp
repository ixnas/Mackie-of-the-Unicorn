//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "MOTUMixer.h"
#include "VirtualMixer.h"
#include <sstream>

namespace MackieOfTheUnicorn::Mixers
{
	MOTUMixer::MOTUMixer(std::unique_ptr<HTTP::HTTPDevice> httpDevice, int id)
	    : HTTPDevice(std::move(httpDevice)), VirtualMixer(nullptr), Id(id)
	{
		HTTPDevice->RegisterCallback(*this);
	}

	void MOTUMixer::SetVirtualMixer(Mixers::VirtualMixer* virtualMixer)
	{
		VirtualMixer = virtualMixer;
	}

	int MOTUMixer::GetId()
	{
		return Id;
	}

	void MOTUMixer::SetInputChannelMute(int originId, int channel, bool on)
	{
		std::ostringstream stringStream;
		stringStream << "mix/chan/" << channel << "/matrix/mute";
		auto key = stringStream.str();
		JSON::JSONValue value;
		value.Float = on ? 1 : 0;
		std::pair<std::string, JSON::JSONValue> message = {key, value};
		HTTPDevice->SendMessage(message);
	}

	void MOTUMixer::HTTPCallback(std::pair<std::string, JSON::JSONValue>& message)
	{
		auto key = message.first;

		// Split key into parts;
		std::vector<std::string> keyParts;
		std::istringstream stringBuffer(key);
		std::string string;
		while (std::getline(stringBuffer, string, '/'))
		{
			keyParts.push_back(string);
		}

		if (keyParts.size() != 5)
		{
			return;
		}

		if (keyParts[0] != "mix" || keyParts[1] != "chan" || keyParts[3] != "matrix" || keyParts[4] != "mute")
		{
			return;
		}

		auto channelNumber = std::stoi(keyParts[2]);
		auto on = message.second.Float.value() == 1;

		VirtualMixer->SetInputChannelMute(Id, channelNumber, on);
	}
} // namespace MackieOfTheUnicorn::Mixers
