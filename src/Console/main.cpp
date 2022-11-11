#include "../Application.h"
#include "../git_version.h"

int main()
{
	std::cout << "Mackie of the Unicorn " << MackieOfTheUnicorn::VERSION << std::endl
	          << "Copyright \u00a9 2022-" << MackieOfTheUnicorn::YEAR << " Sjoerd Scheffer" << std::endl
	          << std::endl;
	auto app = MackieOfTheUnicorn::BuildApplication();
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
