//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#include "MackieDeviceImpl.h"
#include "../Utilities/ShortLabel.h"
#include "../Utilities/FaderValueConverter.h"

namespace MackieOfTheUnicorn::Mackie
{
	static bool IsChannelMuteMessage(std::vector<unsigned char>& message)
	{
		return message[0] == 144 && message[1] >= 16 &&
		       message[1] < 24 &&
		       (message[2] == 127 || message[2] == 0);
	}

	static bool IsChannelSoloMessage(std::vector<unsigned char>& message)
	{
		return message[0] == 144 && message[1] >= 8 &&
			   message[1] < 16 &&
			   (message[2] == 127 || message[2] == 0);
	}

	static bool IsBankForwardMessage(std::vector<unsigned char>& message)
	{
		return message[0] == 144 &&
		       message[1] == 47 &&
		       message[2] == 127;
	}

	static bool IsBankBackwardsMessage(std::vector<unsigned char>& message)
	{
		return message[0] == 144 &&
			   message[1] == 46 &&
			   message[2] == 127;
	}

	static bool IsFaderMessage(std::vector<unsigned char>& message)
	{
		return message[0] >= 0xE0 &&
		       message[0] <= 0xE7;
	}

	MackieDeviceImpl::MackieDeviceImpl(std::unique_ptr<MIDI::MIDIDevice>& midiDevice) : MIDIDevice(std::move(midiDevice))
	{
		MIDIDevice->RegisterCallback(this);
	}

	void MackieDeviceImpl::SetMackieListener(Mackie::MackieListener<MackieDevice>& mackieListener)
	{
		MackieListener = &mackieListener;
	}

	void MackieDeviceImpl::SetChannelMute(int channelNumber, bool on)
	{
		if (channelNumber > 7)
		{
			return;
		}

		const unsigned char byte1 = 144;
		unsigned char byte2 = 16 + channelNumber;
		unsigned char byte3 = on ? 127 : 0;
		std::vector<unsigned char> message = {byte1, byte2, byte3};

		MIDIDevice->SendMessage(message);
	}

	void MackieDeviceImpl::SetChannelSolo(int channelNumber, bool on)
	{
		if (channelNumber > 7)
		{
			return;
		}

		const unsigned char byte1 = 144;
		unsigned char byte2 = 8 + channelNumber;
		unsigned char byte3 = on ? 127 : 0;
		std::vector<unsigned char> message = {byte1, byte2, byte3};

		MIDIDevice->SendMessage(message);
	}

	void MackieDeviceImpl::SetChannelText(int channelNumber, bool onBottomRow, std::string_view text)
	{
		if (channelNumber > 7)
		{
			return;
		}

		std::vector<unsigned char> message;
		message.reserve(text.size() + 8);

		unsigned char offset = onBottomRow ? 0x38 : 0;
		unsigned char start = offset + channelNumber * 7;
		message.insert(message.end(), { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, start });

		auto shortLabel = Utilities::ShortLabel(text).Get();

		for (const char& character : shortLabel)
		{
			message.push_back(character);
		}

		message.push_back(0xF7);

		MIDIDevice->SendMessage(message);
	}

	void MackieDeviceImpl::ClearScreen()
	{
		static std::vector<unsigned char> message = { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00 };
		static bool messageFilled = false;

		if (!messageFilled)
		{
			message.reserve(120);

			for (int i = 0; i < 112; i++)
			{
				message.push_back(' ');
			}

			message.push_back(0xF7);
			messageFilled = true;
		}

		MIDIDevice->SendMessage(message);
	}

	void MackieDeviceImpl::MIDICallback(std::vector<unsigned char>& message)
	{
		if (IsChannelMuteMessage(message))
		{
			auto channelId = message[1] - 16;
			auto on = message[2] == 127;
			MackieListener->OnChannelMutePressed(this, channelId, on);
			return;
		}

		if (IsChannelSoloMessage(message))
		{
			auto channelId = message[1] - 8;
			auto on = message[2] == 127;
			MackieListener->OnChannelSoloPressed(this, channelId, on);
			return;
		}

		if (IsBankForwardMessage(message))
		{
			MackieListener->OnBankForwardPressed();
		}

		if (IsBankBackwardsMessage(message))
		{
			MackieListener->OnBankBackwardsPressed();
		}

		if (IsFaderMessage(message))
		{
			using namespace Utilities;

			auto channelId = message[0] - 0xE0;
			auto value10bit = FaderValueConverter::MackieToInteger10bit({message[1], message[2]});
			auto valueLinear = FaderValueConverter::Integer10bitToLinear(value10bit);

			MackieListener->OnChannelFaderMoved(this, channelId, valueLinear);
		}
	}

	void MackieDeviceImpl::SetChannelFader(int channelNumber, double value)
	{
		if (channelNumber > 7)
		{
			return;
		}

		using namespace Utilities;
		auto integer10bitValue = FaderValueConverter::LinearToInteger10bit(value);
		auto mackieValue = FaderValueConverter::Integer10bitToMackie(integer10bitValue);

		std::vector<unsigned char> message = {(unsigned char)(0xE0 + channelNumber), mackieValue[0], mackieValue[1]};

		MIDIDevice->SendMessage(message);
	}
}