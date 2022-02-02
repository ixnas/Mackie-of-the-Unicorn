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

typedef std::map<int, std::string> GetDevicesRet;
typedef std::unique_ptr<MackieDevice> CreateDeviceRet;
typedef std::unique_ptr<MIDIDevice> CreateDeviceArg;
typedef std::unique_ptr<MackieComposite> CreateCompositeRet;
typedef std::vector<std::unique_ptr<MackieDevice>> CreateCompositeArg;

class MIDIServiceMock : public MIDIService
{
  public:
	MOCK_METHOD(GetDevicesRet, GetDevices, (), (override));
	MOCK_METHOD(std::unique_ptr<MIDIDevice>, GetMIDIDevice, (int), ());
};

class MackieDeviceFactoryMock : public MackieDeviceFactory
{
  public:
	MOCK_METHOD(std::unique_ptr<MackieDevice>, Create, (std::unique_ptr<MIDIDevice>), ());
};

class MackieCompositeFactoryMock : public MackieCompositeFactory
{
  public:
	MOCK_METHOD(std::unique_ptr<MackieComposite>, Create, (std::vector<std::unique_ptr<MackieDevice>>), ());
};

class MackieDeviceMock : public MackieDevice
{
	MOCK_METHOD(void, SetText, (int, std::string), (override));
};

class MIDIDeviceMock : public MIDIDevice
{
	MOCK_METHOD(void, RegisterCallback, (std::function<void(std::vector<unsigned char>)>), (override));
	MOCK_METHOD(void, SendMessage, (std::vector<unsigned char>), (override));
};

class MackieCompositeMock : public MackieComposite
{
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
	GetDevicesRet expected = {{0, "test1"}, {1, "test2"}};

	EXPECT_CALL(*midiService, GetDevices()).Times(1).WillOnce(Return(expected));

	auto actual = instance->GetDevices();

	EXPECT_EQ(expected, actual);
}

TEST_F(MackieServiceImplTest, GetsMIDIDevicesFromMIDIService)
{
	using ::testing::Return;
	using ::testing::ByMove;
	using ::testing::_;
	std::vector<int> input = {5};

	std::unique_ptr<MIDIDevice> midiDevice = std::make_unique<MIDIDeviceMock>();

	EXPECT_CALL(*midiService, GetMIDIDevice(input[0])).Times(1).WillOnce(Return(ByMove(std::move(midiDevice))));

	instance->GetMackieComposite(input);
}

TEST_F(MackieServiceImplTest, GetsMultipleMIDIDevicesFromMIDIService)
{
	using ::testing::Return;
	using ::testing::ByMove;
	using ::testing::_;
	std::vector<int> input = {5, 6};

	std::unique_ptr<MIDIDevice> midiDevice1 = std::make_unique<MIDIDeviceMock>();
	std::unique_ptr<MIDIDevice> midiDevice2 = std::make_unique<MIDIDeviceMock>();

	EXPECT_CALL(*midiService, GetMIDIDevice(input[1])).Times(1).WillOnce(Return(ByMove(std::move(midiDevice1))));
	EXPECT_CALL(*midiService, GetMIDIDevice(input[0])).Times(1).WillOnce(Return(ByMove(std::move(midiDevice2))));

	instance->GetMackieComposite(input);
}

TEST_F(MackieServiceImplTest, CreatesCompositeCorrectly)
{
	using ::testing::Return;
	using ::testing::ByMove;
	using ::testing::_;
	std::vector<int> input = {5};

	std::unique_ptr<MIDIDevice> midiDevice = std::make_unique<MIDIDeviceMock>();

	std::unique_ptr<MackieDevice> mackieDeviceRef = std::make_unique<MackieDeviceMock>();
	std::vector<std::unique_ptr<MackieDevice>> mackieDevicePtrs = {};
	mackieDevicePtrs.push_back(std::move(mackieDeviceRef));

	std::unique_ptr<MackieComposite> mackieComposite = std::make_unique<MackieCompositeMock>();
	MackieComposite* mackieCompositeRef = mackieComposite.get();

	EXPECT_CALL(*midiService, GetMIDIDevice(input[0])).Times(1).WillOnce(Return(ByMove(std::move(midiDevice))));
	EXPECT_CALL(*mackieDeviceFactory, Create(_)).Times(1).WillOnce(Return(ByMove(std::move(mackieDevicePtrs[0]))));
	EXPECT_CALL(*mackieCompositeFactory, Create(_)).Times(1).WillOnce(Return(ByMove(std::move(mackieComposite))));

	auto actual = instance->GetMackieComposite(input);

	EXPECT_NE(nullptr, actual.get());
	EXPECT_EQ(mackieCompositeRef, actual.get());
}