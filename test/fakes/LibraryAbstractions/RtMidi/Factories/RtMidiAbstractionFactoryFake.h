//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORYFAKE_H
#define MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORYFAKE_H

#include "../../../../../src/LibraryAbstractions/RtMidi/Factories/RtMidiAbstractionFactory.h"
#include "../RtMidiOutAbstractionFake.h"
#include "../RtMidiInAbstractionFake.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{
	class RtMidiAbstractionFactoryFake : public RtMidiAbstractionFactory
	{
	  public:
		std::vector<RtMidiInAbstractionFake*> ReturnedInAbstractions;
		std::vector<RtMidiOutAbstractionFake*> ReturnedOutAbstractions;

		std::unique_ptr<RtMidiInAbstraction> CreateInAbstraction() override
		{
			auto inAbstraction = std::make_unique<RtMidiInAbstractionFake>();
			ReturnedInAbstractions.push_back(inAbstraction.get());
			return inAbstraction;
		}

		std::unique_ptr<RtMidiOutAbstraction> CreateOutAbstraction() override
		{
			auto outAbstraction = std::make_unique<RtMidiOutAbstractionFake>();
			ReturnedOutAbstractions.push_back(outAbstraction.get());
			return outAbstraction;
		}
	};
}

#endif // MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORYFAKE_H
