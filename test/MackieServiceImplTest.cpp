//
// Created by Sjoerd Scheffer on 02/02/2022.
//

#include "../src/MackieServiceImpl.h"
#include "../src/MIDIDevice.h"
#include "../src/MIDIService.h"
#include "../src/MackieComposite.h"
#include "../src/MackieCompositeFactory.h"
#include "../src/MackieDevice.h"
#include "../src/MackieDeviceFactory.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MIDIServiceMock : public MIDIService
{
  public:
	MOCK_METHOD((std::map<int, std::string>), GetInputDevices, (), (override));
	MOCK_METHOD((std::map<int, std::string>), GetOutputDevices, (), (override));
	MOCK_METHOD(std::unique_ptr<MIDIDevice>, GetMIDIDevice, (int, int), ());
};

class MackieDeviceFactoryMock : public MackieDeviceFactory
{
  public:
	std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDIDevice> midiDevice) override
	{
		return CreateProxy(midiDevice.get());
	}
	MOCK_METHOD(std::unique_ptr<MackieDevice>, CreateProxy, (MIDIDevice*), ());
};

class MackieCompositeFactoryMock : public MackieCompositeFactory
{
	std::unique_ptr<MackieComposite> Create(std::vector<std::unique_ptr<MackieDevice>> mackieDevices) override
	{
		std::vector<MackieDevice*> mackieDevicePtrs;
		std::transform(mackieDevices.begin(), mackieDevices.end(), std::back_inserter(mackieDevicePtrs),
		               [](std::unique_ptr<MackieDevice>& p) { return p.get(); });
		return std::unique_ptr<MackieComposite>(CreateProxy(mackieDevicePtrs));
	}

  public:
	MOCK_METHOD(std::unique_ptr<MackieComposite>, CreateProxy, (std::vector<MackieDevice*>), ());
};

class MackieDeviceMock : public MackieDevice
{
  public:
	MOCK_METHOD(void, SetText, (int, std::string), (override));
};

class MIDIDeviceMock : public MIDIDevice
{
  public:
	MOCK_METHOD(void, RegisterCallback, (std::function<void(std::vector<unsigned char>)>), (override));
	MOCK_METHOD(void, SendMessage, (std::vector<unsigned char>), (override));
};

class MackieCompositeMock : public MackieComposite
{
  public:
	MOCK_METHOD(void, AddMackieDevice, (std::unique_ptr<MackieDevice>), (override));
	MOCK_METHOD(void, SetText, (int, std::string), (override));
};

class MackieServiceImplTest : public ::testing::Test
{
  protected:
	void SetUp() override
	{
		mackieDeviceFactory = std::make_unique<MackieDeviceFactoryMock>();
		mackieCompositeFactory = std::make_unique<MackieCompositeFactoryMock>();
		midiService = std::make_unique<MIDIServiceMock>();
		instance = std::make_unique<MackieServiceImpl>(*mackieCompositeFactory, *mackieDeviceFactory, *midiService);
	}

	std::unique_ptr<MackieServiceImpl> instance;
	std::unique_ptr<MackieDeviceFactoryMock> mackieDeviceFactory;
	std::unique_ptr<MackieCompositeFactoryMock> mackieCompositeFactory;
	std::unique_ptr<MIDIServiceMock> midiService;
};

TEST_F(MackieServiceImplTest, GetsDevicesListFromMIDIService)
{
	using ::testing::Return;
	std::map<int, std::string> expectedInput = {{0, "test1"}, {1, "test2"}};
	std::map<int, std::string> expectedOutput = {{0, "test3"}, {1, "test4"}};

	EXPECT_CALL(*midiService, GetInputDevices()).Times(1).WillOnce(Return(expectedInput));
	EXPECT_CALL(*midiService, GetOutputDevices()).Times(1).WillOnce(Return(expectedOutput));

	auto actualInput = instance->GetInputDevices();
	auto actualOutput = instance->GetOutputDevices();

	EXPECT_EQ(expectedInput, actualInput);
	EXPECT_EQ(expectedOutput, actualOutput);
}

TEST_F(MackieServiceImplTest, GetsMIDIDevicesFromMIDIService)
{
	using ::testing::_;
	using ::testing::ByMove;
	using ::testing::Return;
	std::vector<std::pair<int, int>> input = { {5, 6} };

	std::unique_ptr<MIDIDevice> midiDevice = std::make_unique<MIDIDeviceMock>();

	EXPECT_CALL(*midiService, GetMIDIDevice(input[0].first, input[0].second)).Times(1).WillOnce(Return(ByMove(std::move(midiDevice))));

	instance->GetMackieComposite(input);
}

TEST_F(MackieServiceImplTest, GetsMultipleMIDIDevicesFromMIDIService)
{
	using ::testing::_;
	using ::testing::ByMove;
	using ::testing::Return;
	std::vector<std::pair<int, int>> input = { {5, 6}, {8, 9}};

	auto midiDevice1 = std::make_unique<MIDIDeviceMock>();
	auto midiDevice2 = std::make_unique<MIDIDeviceMock>();

	EXPECT_CALL(*midiService, GetMIDIDevice(input[0].first, input[0].second)).Times(1).WillOnce(Return(ByMove(std::move(midiDevice1))));
	EXPECT_CALL(*midiService, GetMIDIDevice(input[1].first, input[1].second)).Times(1).WillOnce(Return(ByMove(std::move(midiDevice2))));

	instance->GetMackieComposite(input);
}

TEST_F(MackieServiceImplTest, CreatesCompositeCorrectly)
{
	using ::testing::_;
	using ::testing::ByMove;
	using ::testing::Return;
	std::vector<std::pair<int, int>> input = { {5, 6}, {8, 9} };

	auto midiDevice1 = std::make_unique<MIDIDeviceMock>();
	MIDIDevice* midiDevice1Ref = midiDevice1.get();

	auto midiDevice2 = std::make_unique<MIDIDeviceMock>();
	MIDIDevice* midiDevice2Ref = midiDevice2.get();

	auto mackieDevice1 = std::make_unique<MackieDeviceMock>();
	auto mackieDevice2 = std::make_unique<MackieDeviceMock>();

	std::vector<MackieDevice*> mackieDevicePtrs;
	mackieDevicePtrs.push_back(mackieDevice1.get());
	mackieDevicePtrs.push_back(mackieDevice2.get());

	std::vector<std::unique_ptr<MackieDevice>> mackieDevices = {};
	mackieDevices.push_back(std::move(mackieDevice1));
	mackieDevices.push_back(std::move(mackieDevice2));

	auto mackieComposite = std::make_unique<MackieCompositeMock>();
	MackieComposite* mackieCompositeRef = mackieComposite.get();

	EXPECT_CALL(*midiService, GetMIDIDevice(input[0].first, input[0].second)).Times(1).WillOnce(Return(ByMove(std::move(midiDevice1))));
	EXPECT_CALL(*midiService, GetMIDIDevice(input[1].first, input[1].second)).Times(1).WillOnce(Return(ByMove(std::move(midiDevice2))));
	EXPECT_CALL(*mackieDeviceFactory, CreateProxy(midiDevice1Ref))
	    .Times(1)
	    .WillOnce(Return(ByMove(std::move(mackieDevices[0]))));
	EXPECT_CALL(*mackieDeviceFactory, CreateProxy(midiDevice2Ref))
		.Times(1)
		.WillOnce(Return(ByMove(std::move(mackieDevices[1]))));
	EXPECT_CALL(*mackieCompositeFactory, CreateProxy(mackieDevicePtrs))
	    .Times(1)
	    .WillOnce(Return(ByMove(std::move(mackieComposite))));

	auto actual = instance->GetMackieComposite(input);

	EXPECT_NE(nullptr, actual.get());
	EXPECT_EQ(mackieCompositeRef, actual.get());
}