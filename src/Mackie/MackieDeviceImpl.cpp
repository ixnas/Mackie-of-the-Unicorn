//
// Created by Sjoerd Scheffer on 14/02/2022.
//

#include "MackieDeviceImpl.h"
#include "../Utilities/ShortLabel.h"

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
		std::vector<unsigned char> message = { 0xF0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00 };
		for (int i = 0; i < 112; i++)
		{
			message.push_back(' ');
		}

		message.push_back(0xF7);
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
	}
}