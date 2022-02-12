//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORYIMPL_H
#define MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORYIMPL_H

#include "RtMidiAbstractionFactory.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{
	class RtMidiAbstractionFactoryImpl : public RtMidiAbstractionFactory
	{
		std::unique_ptr<RtMidiInAbstraction> CreateInAbstraction() override;
		std::unique_ptr<RtMidiOutAbstraction> CreateOutAbstraction() override;
	};
}

#endif // MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORYIMPL_H
