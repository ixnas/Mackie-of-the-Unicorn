//
// Created by Sjoerd Scheffer on 24/02/2022.
//
//
// Created by Sjoerd Scheffer on 20/02/2022.
//

#include "ApplicationContainer.h"

namespace MackieOfTheUnicorn::Tests::Integration
{
	ApplicationContainer::ApplicationContainer(
	    MackieOfTheUnicorn::Application& application,
	    MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories::CurlAbstractionFactory& curlAbstractionFactory,
	    MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory& rtMidiAbstractionFactory)
	    : Application(&application), CurlAbstractionFactory(&curlAbstractionFactory),
	      RtMidiAbstractionFactory(&rtMidiAbstractionFactory)
	{
	}

	ApplicationContainerWrapper::ApplicationContainerWrapper(
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

	std::unique_ptr<ApplicationContainerWrapper> GetApplicationContainerWrapper()
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

		auto rtMidiInAbstractionFake = *(rtMidiAbstractionFactoryFake->ReturnedInAbstractions.end() - 1);
		auto rtMidiOutAbstractionFake = *(rtMidiAbstractionFactoryFake->ReturnedOutAbstractions.end() - 1);

		rtMidiInAbstractionFake->PortCount = 1;
		rtMidiInAbstractionFake->PortName = "input1";
		rtMidiOutAbstractionFake->PortCount = 1;
		rtMidiOutAbstractionFake->PortName = "output1";

		std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
		applicationContainer.Application->Start(inputAndOutputIds);

		rtMidiInAbstractionFake = *(rtMidiAbstractionFactoryFake->ReturnedInAbstractions.end() - 1);
		rtMidiOutAbstractionFake = *(rtMidiAbstractionFactoryFake->ReturnedOutAbstractions.end() - 1);

		auto curlInAbstractionFake = *(curlAbstractionFactoryFake->CreateCurlAbstractionFakes.end() - 2);
		auto curlOutAbstractionFake = *(curlAbstractionFactoryFake->CreateCurlAbstractionFakes.end() - 1);

		return std::make_unique<ApplicationContainerWrapper>(applicationContainer, rtMidiInAbstractionFake,
		                                                     rtMidiOutAbstractionFake, curlInAbstractionFake,
		                                                     curlOutAbstractionFake);
	}
} // namespace MackieOfTheUnicorn::Tests::Integration
