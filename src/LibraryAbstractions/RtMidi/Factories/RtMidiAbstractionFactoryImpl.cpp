//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#include "RtMidiAbstractionFactoryImpl.h"
#include "../RtMidiInAbstractionImpl.h"
#include "../RtMidiOutAbstractionImpl.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{

	std::unique_ptr<RtMidiInAbstraction> RtMidiAbstractionFactoryImpl::CreateInAbstraction()
	{
		return std::make_unique<RtMidiInAbstractionImpl>();
	}

	std::unique_ptr<RtMidiOutAbstraction> RtMidiAbstractionFactoryImpl::CreateOutAbstraction()
	{
		return std::make_unique<RtMidiOutAbstractionImpl>();
	}

}
