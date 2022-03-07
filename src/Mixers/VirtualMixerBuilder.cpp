//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#include "VirtualMixerBuilder.h"
#include "../Exceptions/DeviceUnavailableException.h"
#include "../Mackie/MackieService.h"
#include "VirtualMixerImpl.h"

namespace MackieOfTheUnicorn::Mixers
{
	template <class T1, class T2>
	static bool CheckInAndOutputPairs(std::map<T1, T2>& inputs, std::map<T1, T2>& outputs,
	                                  std::vector<std::pair<T1, T1>>& inputAndOutputIds)
	{
		return std::all_of(inputAndOutputIds.begin(), inputAndOutputIds.end(),
		                   [&inputs, &outputs](std::pair<T1, T1> pair) {
			                   return inputs.contains(pair.first) && outputs.contains(pair.second);
		                   });
	}

	VirtualMixerBuilder::VirtualMixerBuilder(Mackie::MackieService& mackieService,
	                                         HTTP::Factories::HTTPDeviceFactory& httpDeviceFactory)
	    : MackieService(&mackieService), CurrentMixerId(0), HTTPDeviceFactory(&httpDeviceFactory)
	{
	}

	VirtualMixerBuilder* VirtualMixerBuilder::AddMackieMixer(std::vector<std::pair<int, int>>& inputAndOutputIds)
	{
		auto availableInputs = MackieService->GetInputDevices();
		auto availableOutputs = MackieService->GetOutputDevices();

		auto allRequestedPairsAreAvailable =
		    CheckInAndOutputPairs(availableInputs, availableOutputs, inputAndOutputIds);

		if (!allRequestedPairsAreAvailable)
		{
			throw Exceptions::DeviceUnavailableException("Device not available.");
		}

		auto mackieComposite = MackieService->GetMackieComposite(inputAndOutputIds);
		MackieMixer = std::make_unique<Mixers::MackieMixer>(mackieComposite, CurrentMixerId++);

		return this;
	}

	VirtualMixerBuilder* VirtualMixerBuilder::AddMOTUMixer(std::string hostname)
	{
		std::ostringstream stringStream;
		stringStream << "http://" << hostname << "/datastore";
		auto url = stringStream.str();
		auto httpDevice = HTTPDeviceFactory->Create(url);
		MOTUMixer = std::make_unique<Mixers::MOTUMixer>(std::move(httpDevice), CurrentMixerId++);
		return this;
	}

	std::unique_ptr<VirtualMixer> VirtualMixerBuilder::Build()
	{
		if (MackieMixer == nullptr)
		{
			throw Exceptions::DeviceUnavailableException("No MackieMixer added.");
		}

		if (MOTUMixer == nullptr)
		{
			throw Exceptions::DeviceUnavailableException("No MOTUMixer added.");
		}

		std::vector<std::unique_ptr<LinkedMixer>> linkedMixers;
		linkedMixers.push_back(std::move(MackieMixer));
		linkedMixers.push_back(std::move(MOTUMixer));
		auto virtualMixer = std::make_unique<VirtualMixerImpl>(linkedMixers);
		MackieMixer = nullptr;
		return virtualMixer;
	}
} // namespace MackieOfTheUnicorn::Mixers