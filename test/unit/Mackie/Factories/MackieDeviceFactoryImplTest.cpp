//
// Created by Sjoerd Scheffer on 16/02/2022.
//

#include "gtest/gtest.h"
#include "../../../../src/Mackie/Factories/MackieDeviceFactoryImpl.h"
#include "../../../fakes/MIDI/MIDIDeviceFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::Mackie::Factories
{
	class MackieDeviceFactoryImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			midiDeviceFake = std::make_unique<MackieOfTheUnicorn::MIDI::MIDIDeviceFake>(0, 0);
			instance = std::make_unique<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryImpl>();
		}

		std::unique_ptr<MackieOfTheUnicorn::MIDI::MIDIDevice> midiDeviceFake;
		std::unique_ptr<MackieOfTheUnicorn::Mackie::Factories::MackieDeviceFactoryImpl> instance;
	};

	TEST_F(MackieDeviceFactoryImplTest, ReturnsProperDevice)
	{
		auto actualDevice = instance->Create(midiDeviceFake);

		EXPECT_NE(actualDevice.get(), nullptr);
	}

} // namespace MackieOfTheUnicorn::Tests::Unit::Mackie::Factories
