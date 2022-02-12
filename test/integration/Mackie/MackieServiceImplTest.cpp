//
// Created by Sjoerd Scheffer on 06/02/2022.
//
#include "../../../src/Mackie/MackieServiceImpl.h"
#include "../../../src/Mackie/MackieDevice.h"
#include "../../fakes/MIDI/MIDIServiceFake.h"
#include "../../fakes/Mackie/Factories/MackieCompositeFactoryFake.h"
#include "gtest/gtest.h"

namespace MackieOfTheUnicorn::Tests::Integration::Mackie
{
	using namespace MackieOfTheUnicorn::Mackie;

	class MackieServiceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			mackieCompositeFactory = std::make_unique<Factories::MackieCompositeFactoryFake>();
			midiService = std::make_unique<MIDI::MIDIServiceFake>();
			instance = std::make_unique<MackieServiceImpl>(*mackieCompositeFactory, *midiService);
		}

		std::unique_ptr<MackieServiceImpl> instance;
		std::unique_ptr<Factories::MackieCompositeFactoryFake> mackieCompositeFactory;
		std::unique_ptr<MIDI::MIDIServiceFake> midiService;
	};

} // namespace MackieOfTheUnicorn::Tests::Integration::Mackie
