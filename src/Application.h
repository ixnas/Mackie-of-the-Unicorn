//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_APPLICATION_H
#define MACKIE_OF_THE_UNICORN_APPLICATION_H

#include "Mixers/MackieMixer.h"
#include "Mixers/VirtualMixer.h"
#include "Mixers/VirtualMixerBuilder.h"

namespace MackieOfTheUnicorn::Mackie
{
	class MackieService;
}

namespace MackieOfTheUnicorn
{
	/// The main application controller.
	class Application
	{
		Mackie::MackieService* MackieService;
		Mixers::VirtualMixerBuilder* VirtualMixerBuilder;
		std::unique_ptr<Mixers::VirtualMixer> VirtualMixer;

	  public:
		explicit Application(Mackie::MackieService& mackieService, Mixers::VirtualMixerBuilder& virtualMixerBuilder);

		/// Returns a list of available MIDI input devices.
		[[nodiscard]] std::map<int, std::string> GetAvailableInputDevices() const;

		/// Returns a list of available MIDI output devices.
		[[nodiscard]] std::map<int, std::string> GetAvailableOutputDevices() const;

		/// Start the application using the specified MIDI device numbers.
		void Start(std::vector<std::pair<int, int>>& inputAndOutputIds, std::string& hostname);
	};

	Application BuildApplication();
} // namespace MackieOfTheUnicorn

#endif // MACKIE_OF_THE_UNICORN_APPLICATION_H
