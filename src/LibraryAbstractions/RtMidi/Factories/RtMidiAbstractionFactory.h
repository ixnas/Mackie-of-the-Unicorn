//
// Created by Sjoerd Scheffer on 12/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORY_H
#define MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORY_H

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi
{
	class RtMidiInAbstraction;
	class RtMidiOutAbstraction;
}

namespace MackieOfTheUnicorn::LibraryAbstractions::RtMidi::Factories
{
	/// Creates abstracted RtMidi interfaces.
	class RtMidiAbstractionFactory
	{
	  public:
		virtual ~RtMidiAbstractionFactory() = default;

		/// Returns a new RtMidiIn instance.
		virtual std::unique_ptr<RtMidiInAbstraction> CreateInAbstraction() = 0;

		/// Returns a new RtMidiOut instance.
		virtual std::unique_ptr<RtMidiOutAbstraction> CreateOutAbstraction() = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_RTMIDIABSTRACTIONFACTORY_H
