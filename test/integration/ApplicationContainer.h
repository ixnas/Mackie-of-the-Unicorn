//
// Created by Sjoerd Scheffer on 20/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_APPLICATIONCONTAINER_H
#define MACKIE_OF_THE_UNICORN_APPLICATIONCONTAINER_H

#include "../../src/Application.h"
#include "../../src/HTTP/Factories/HTTPDeviceFactoryImpl.h"
#include "../../src/LibraryAbstractions/Curl/Factories/CurlAbstractionFactory.h"
#include "../../src/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactory.h"
#include "../../src/MIDI/Factories/MIDIDeviceFactoryImpl.h"
#include "../../src/MIDI/MIDIServiceImpl.h"
#include "../../src/Mackie/Factories/MackieCompositeFactoryImpl.h"
#include "../../src/Mackie/Factories/MackieDeviceFactoryImpl.h"
#include "../../src/Mackie/MackieServiceImpl.h"
#include "../../src/di.h"
#include "../fakes/LibraryAbstractions/Curl/Factories/CurlAbstractionFactoryFake.h"
#include "../fakes/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryFake.h"
#include <vector>

namespace MackieOfTheUnicorn::Tests::Integration
{
	struct ApplicationContainer
	{
		Application* Application;
		MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactory* CurlAbstractionFactory;
		MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory* RtMidiAbstractionFactory;

		explicit ApplicationContainer(
		    MackieOfTheUnicorn::Application& application,
		    MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactory& curlAbstractionFactory,
		    MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory&
		        rtMidiAbstractionFactory)
		    : Application(&application), CurlAbstractionFactory(&curlAbstractionFactory),
		      RtMidiAbstractionFactory(&rtMidiAbstractionFactory)
		{
		}
	};

	struct ApplicationContainerWrapper
	{
		ApplicationContainer ApplicationContainer;
		LibraryAbstractions::RtMidi::RtMidiInAbstractionFake* RtMidiInAbstractionFake;
		LibraryAbstractions::RtMidi::RtMidiOutAbstractionFake* RtMidiOutAbstractionFake;
		LibraryAbstractions::Curl::CurlAbstractionFake* CurlInAbstractionFake;
		LibraryAbstractions::Curl::CurlAbstractionFake* CurlOutAbstractionFake;

		explicit ApplicationContainerWrapper(
		    Integration::ApplicationContainer applicationContainer,
		    LibraryAbstractions::RtMidi::RtMidiInAbstractionFake* rtMidiInAbstractionFake,
		    LibraryAbstractions::RtMidi::RtMidiOutAbstractionFake* rtMidiOutAbstractionFake,
		    LibraryAbstractions::Curl::CurlAbstractionFake* curlInAbstractionFake,
		    LibraryAbstractions::Curl::CurlAbstractionFake* curlOutAbstractionFake)
		    : ApplicationContainer(applicationContainer), RtMidiInAbstractionFake(rtMidiInAbstractionFake),
		      RtMidiOutAbstractionFake(rtMidiOutAbstractionFake), CurlInAbstractionFake(curlInAbstractionFake),
		      CurlOutAbstractionFake(curlOutAbstractionFake)
		{
		}
	};

	auto GetApplicationContainerWrapper()
	{
		auto injector = di::make_injector(
		    di::bind<MackieOfTheUnicorn::Mackie::MackieService>.to<MackieOfTheUnicorn::Mackie::MackieServiceImpl>(),
		    di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactoryImpl>(),
		    di::bind<MackieOfTheUnicorn::MIDI::MIDIService>.to<MackieOfTheUnicorn::MIDI::MIDIServiceImpl>(),
		    di::bind<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactory>.to<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryImpl>(),
		    di::bind<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory>.to<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake>(),
		    di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryImpl>(),
		    di::bind<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactory>.to<MackieOfTheUnicorn::HTTP::Factories::HTTPDeviceFactoryImpl>(),
		    di::bind<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactory>.to<MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryFake>());
		auto applicationContainer = injector.create<MackieOfTheUnicorn::Tests::Integration::ApplicationContainer>();

		auto rtMidiAbstractionFactoryFake =
		    dynamic_cast<LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryFake*>(
		        applicationContainer.RtMidiAbstractionFactory);
		auto curlAbstractionFactoryFake =
		    dynamic_cast<LibraryAbstractions::Curl::Factories::CurlAbstractionFactoryFake*>(
		        applicationContainer.CurlAbstractionFactory);

		auto rtMidiInAbstractionFake = rtMidiAbstractionFactoryFake->ReturnedInAbstractions[0];
		auto rtMidiOutAbstractionFake = rtMidiAbstractionFactoryFake->ReturnedOutAbstractions[0];

		rtMidiInAbstractionFake->PortCount = 1;
		rtMidiInAbstractionFake->PortName = "input1";
		rtMidiOutAbstractionFake->PortCount = 1;
		rtMidiOutAbstractionFake->PortName = "output1";

		std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
		applicationContainer.Application->Start(inputAndOutputIds);

		rtMidiInAbstractionFake = rtMidiAbstractionFactoryFake->ReturnedInAbstractions[1];
		rtMidiOutAbstractionFake = rtMidiAbstractionFactoryFake->ReturnedOutAbstractions[1];

		auto curlInAbstractionFake = curlAbstractionFactoryFake->CreateCurlAbstractionFakes[0];
		auto curlOutAbstractionFake = curlAbstractionFactoryFake->CreateCurlAbstractionFakes[1];

		return std::make_unique<ApplicationContainerWrapper>(applicationContainer, rtMidiInAbstractionFake,
		                                                     rtMidiOutAbstractionFake, curlInAbstractionFake,
		                                                     curlOutAbstractionFake);
	}
} // namespace MackieOfTheUnicorn::Tests::Integration

#endif // MACKIE_OF_THE_UNICORN_APPLICATIONCONTAINER_H
