//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORY_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORY_H

namespace MackieOfTheUnicorn::Mackie
{
	class MackieComposite;
}

namespace MackieOfTheUnicorn::Mackie::Factories
{
	/// Creates Mackie composite device interfaces using MIDI port numbers.
	class MackieCompositeFactory
	{
	  public:
		virtual ~MackieCompositeFactory() = default;

		/// Returns a new Mackie composite device using pairs of MIDI input and output port numbers.
		virtual std::unique_ptr<MackieComposite> Create(const std::vector<std::pair<int, int>>& inputAndOutputIds) = 0;
	};
} // namespace MackieOfTheUnicorn::Mackie::Factories

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFACTORY_H
