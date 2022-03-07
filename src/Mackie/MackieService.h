//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIESERVICE_H
#define MACKIE_OF_THE_UNICORN_MACKIESERVICE_H

namespace MackieOfTheUnicorn::Mackie
{
	class MackieComposite;

	/// Service used to get connected Mackie controllers.
	class MackieService
	{
	  public:
		virtual ~MackieService() = default;

		/// Returns a list of available MIDI input devices.
		virtual std::map<int, std::string> GetInputDevices() = 0;

		/// Returns a list of available MIDI output devices.
		virtual std::map<int, std::string> GetOutputDevices() = 0;

		/// Returns a composite of one or more Mackies using pairs of MIDI input and output port numbers.
		virtual std::unique_ptr<MackieComposite> GetMackieComposite(
		    const std::vector<std::pair<int, int>>& inAndOutIds) = 0;
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIESERVICE_H
