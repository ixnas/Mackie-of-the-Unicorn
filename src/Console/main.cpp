#include "../Application.h"
#include "../LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactoryImpl.h"
#include "../LibraryAbstractions/RtMidi/RtMidiInAbstractionImpl.h"
#include "../LibraryAbstractions/RtMidi/RtMidiOutAbstractionImpl.h"
#include "../MIDI/Factories/MIDIDeviceFactoryImpl.h"
#include "../MIDI/MIDIServiceImpl.h"
#include "../Mackie/Factories/MackieCompositeFactoryImpl.h"
#include "../Mackie/Factories/MackieDeviceFactoryImpl.h"
#include "../Mackie/MackieServiceImpl.h"
#include "../di.h"
#include "../git_version.h"
#include <curl/curl.h>
#include <sstream>

int main()
{
	std::cout << "Mackie of the Unicorn " << MackieOfTheUnicorn::VERSION << std::endl << "Copyright \u00a9 2022 Sjoerd Scheffer" << std::endl << std::endl;
	auto injector = di::make_injector(
	    di::bind<MackieOfTheUnicorn::Mackie::MackieService>.to<MackieOfTheUnicorn::Mackie::MackieServiceImpl>(),
	    di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieCompositeFactoryImpl>(),
	    di::bind<MackieOfTheUnicorn::MIDI::MIDIService>.to<MackieOfTheUnicorn::MIDI::MIDIServiceImpl>(),
	    di::bind<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactory>.to<MackieOfTheUnicorn::MIDI::Factories::MIDIDeviceFactoryImpl>(),
	    di::bind<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactory>.to<MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories::RtMidiAbstractionFactoryImpl>(),
	    di::bind<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactory>.to<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryImpl>());
	auto app = injector.create<MackieOfTheUnicorn::Application>();
	auto inputDevices = app.GetAvailableInputDevices();
	auto outputDevices = app.GetAvailableOutputDevices();

	std::cout << "Input devices:" << std::endl;
	for (const auto& inputDevice : inputDevices)
	{
		std::cout << inputDevice.first << ": " << inputDevice.second << std::endl;
	}

	std::cout << std::endl << "Output devices:" << std::endl;
	for (const auto& outputDevice : outputDevices)
	{
		std::cout << outputDevice.first << ": " << outputDevice.second << std::endl;
	}

	std::vector<std::pair<int, int>> inputAndOutputIds = {{0, 0}};
	app.Start(inputAndOutputIds);

	getchar();
}
