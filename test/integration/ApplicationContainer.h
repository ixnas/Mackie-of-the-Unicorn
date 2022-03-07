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
		        rtMidiAbstractionFactory);
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
		    LibraryAbstractions::Curl::CurlAbstractionFake* curlOutAbstractionFake);
	};

	std::unique_ptr<ApplicationContainerWrapper> GetApplicationContainerWrapper();
} // namespace MackieOfTheUnicorn::Tests::Integration

#endif // MACKIE_OF_THE_UNICORN_APPLICATIONCONTAINER_H
