//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "MOTUMixer.h"
#include "VirtualMixer.h"
#include "../Utilities/FaderValueConverter.h"

namespace MackieOfTheUnicorn::Mixers
{
	static std::vector<std::string> SplitKey(std::string& key)
	{
		std::vector<std::string> keyParts;
		std::istringstream stringBuffer(key);
		std::string string;
		while (std::getline(stringBuffer, string, '/'))
		{
			keyParts.push_back(string);
		}

		return keyParts;
	}

	static bool IsMuteMessage(std::vector<std::string>& keyParts)
	{
		if (keyParts.size() != 5)
		{
			return false;
		}

		if (keyParts[0] != "mix" || keyParts[1] != "chan" || keyParts[3] != "matrix" || keyParts[4] != "mute")
		{
			return false;
		}

		return true;
	}

	static bool IsSoloMessage(std::vector<std::string>& keyParts)
	{
		if (keyParts.size() != 5)
		{
			return false;
		}

		if (keyParts[0] != "mix" || keyParts[1] != "chan" || keyParts[3] != "matrix" || keyParts[4] != "solo")
		{
			return false;
		}

		return true;
	}

	static bool IsFaderMessage(std::vector<std::string>& keyParts)
	{
		if (keyParts.size() != 5)
		{
			return false;
		}

		if (keyParts[0] != "mix" || keyParts[1] != "chan" || keyParts[3] != "matrix" || keyParts[4] != "fader")
		{
			return false;
		}

		return true;
	}

	MOTUMixer::MOTUMixer(std::unique_ptr<HTTP::HTTPDevice> httpDevice, int id)
	    : HTTPDevice(std::move(httpDevice)), VirtualMixer(nullptr), Id(id)
	{
		HTTPDevice->RegisterCallback(*this);
	}

	void MOTUMixer::SetVirtualMixer(Mixers::VirtualMixer* virtualMixer)
	{
		VirtualMixer = virtualMixer;
		HTTPDevice->StartListening();
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
		value.Integer = on ? 1 : 0;
		std::pair<std::string, JSON::JSONValue> message = {key, value};
		HTTPDevice->SendMessage(message);
	}

	void MOTUMixer::SetInputChannelSolo(int originId, int channel, bool on)
	{
		std::ostringstream stringStream;
		stringStream << "mix/chan/" << channel << "/matrix/solo";
		auto key = stringStream.str();
		JSON::JSONValue value;
		value.Integer = on ? 1 : 0;
		std::pair<std::string, JSON::JSONValue> message = {key, value};
		HTTPDevice->SendMessage(message);
	}

	void MOTUMixer::SetInputChannelLabel(int originId, int channel, std::string_view label)
	{
	}

	void MOTUMixer::HTTPCallback(std::pair<std::string, JSON::JSONValue>& message)
	{
		auto key = message.first;
		auto keyParts = SplitKey(key);

		if (IsMuteMessage(keyParts))
		{
			auto channelNumber = std::stoi(keyParts[2]);
			auto on = message.second.Float.value() == 1;

			VirtualMixer->SetInputChannelMute(Id, channelNumber, on);
			return;
		}

		if (IsSoloMessage(keyParts))
		{
			auto channelNumber = std::stoi(keyParts[2]);
			auto on = message.second.Float.value() == 1;

			VirtualMixer->SetInputChannelSolo(Id, channelNumber, on);
			return;
		}

		if (IsFaderMessage(keyParts))
		{
			using namespace Utilities;

			auto channelNumber = std::stoi(keyParts[2]);
			auto value = message.second.Float.value();
			auto valueLinear = FaderValueConverter::MotuToLinear(value);

			VirtualMixer->SetInputChannelFader(Id, channelNumber, valueLinear);
		}

		// Move this stuff to HTTP layer
		std::pair<std::vector<std::string>, JSON::JSONValue> messageInParts = {keyParts, message.second};
		auto labels = LabelCache.GetLabels(messageInParts);

		if (labels.empty())
		{
			return;
		}

		for (const auto& label : labels)
		{
			VirtualMixer->SetInputChannelLabel(Id, label.first, label.second);
		}
	}

	void MOTUMixer::SetInputChannelFader(int originId, int channel, double value)
	{
		using namespace Utilities;

		std::ostringstream stringStream;
		stringStream << "mix/chan/" << channel << "/matrix/fader";
		auto key = stringStream.str();
		JSON::JSONValue motuValue;
		motuValue.Float = FaderValueConverter::LinearToMotu(value);
		std::pair<std::string, JSON::JSONValue> message = {key, motuValue};
		HTTPDevice->SendMessage(message);
	}
} // namespace MackieOfTheUnicorn::Mixers
