//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "Application.h"
#include "di.h"
#include "HTTP/Factories/HTTPDeviceFactoryImpl.h"
#include "LibraryAbstractions/Curl/Factories/CurlAbstractionFactoryImpl.h"
#include "LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryImpl.h"
#include "LibraryAbstractions/RtMidi/RtMidiInAbstractionImpl.h"
#include "LibraryAbstractions/RtMidi/RtMidiOutAbstractionImpl.h"
#include "MIDI/Factories/MIDIDeviceFactoryImpl.h"
#include "MIDI/MIDIServiceImpl.h"
#include "Mackie/Factories/MackieCompositeFactoryImpl.h"
#include "Mackie/Factories/MackieDeviceFactoryImpl.h"
#include "Mackie/MackieServiceImpl.h"

namespace MackieOfTheUnicorn
{
	Application::Application(Mackie::MackieService& mackieService, Mixers::VirtualMixerBuilder& virtualMixerBuilder) : MackieService(&mackieService), VirtualMixerBuilder(&virtualMixerBuilder)
	{
	}

	std::map<int, std::string> Application::GetAvailableInputDevices() const
	{
		return MackieService->GetInputDevices();
	}

	std::map<int, std::string> Application::GetAvailableOutputDevices() const
	{
		return MackieService->GetOutputDevices();
	}

	void Application::Start(std::vector<std::pair<int, int>>& inputAndOutputIds)
	{
		VirtualMixer = VirtualMixerBuilder->AddMackieMixer(inputAndOutputIds)->AddMOTUMixer("127.0.0.1:1280/0001f2fffe01421e")->Build();
	}

	Application BuildApplication()
	{
		auto injector = di::make_injector(
			di::bind<MackieOfTheUnicorn::Mackie::MackieService>.to<MackieOfTheUnicorn::Mackie::MackieServiceImpl>(),
			di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactoryImpl>(),
			di::bind<MackieOfTheUnicorn::MIDI::MIDIService>.to<MackieOfTheUnicorn::MIDI::MIDIServiceImpl>(),
			di::bind<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactory>.to<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryImpl>(),
			di::bind<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory>.to<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryImpl>(),
			di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryImpl>(),
			di::bind<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactory>.to<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactoryImpl>(),
			di::bind<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactory>.to<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryImpl>());
		return injector.create<MackieOfTheUnicorn::Application>();
	}
} // namespace MackieOfTheUnicorn