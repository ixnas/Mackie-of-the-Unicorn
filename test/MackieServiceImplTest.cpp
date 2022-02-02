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
	std::unique_ptr<MIDIDevice> GetMIDIDevice(int id) override
	{
		return std::unique_ptr<MIDIDevice>(GetMIDIDeviceProxy(id));
	}

	MOCK_METHOD(GetDevicesRet, GetDevices, (), (override));
	MOCK_METHOD(MIDIDevice*, GetMIDIDeviceProxy, (int), ());
};

class MackieDeviceFactoryMock : public MackieDeviceFactory
{
  public:
	std::unique_ptr<MackieDevice> Create(std::unique_ptr<MIDIDevice> midiDevice) override
	{
		return std::unique_ptr<MackieDevice>(CreateProxy(midiDevice.get()));
	}

	MOCK_METHOD(MackieDevice*, CreateProxy, (MIDIDevice*), ());
};

class MackieCompositeFactoryMock : public MackieCompositeFactory
{
  public:
	std::unique_ptr<MackieComposite> Create(std::vector<std::unique_ptr<MackieDevice>> mackieDevices) override
	{
		std::vector<MackieDevice*> mackieDevicePtrs;
		std::transform(mackieDevices.begin(), mackieDevices.end(), std::back_inserter(mackieDevicePtrs),
		               [](std::unique_ptr<MackieDevice>& p) { return p.get(); });
		return std::unique_ptr<MackieComposite>(CreateProxy(mackieDevicePtrs));
	}

	MOCK_METHOD(MackieComposite*, CreateProxy, (std::vector<MackieDevice*>), ());
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
	std::vector<int> input = {5};

	MIDIDeviceMock midiDevice;
	MIDIDevice* midiDeviceRef = &midiDevice;

	EXPECT_CALL(*midiService, GetMIDIDeviceProxy(input[0])).Times(1).WillOnce(Return(midiDeviceRef));

	instance->GetMackieComposite(input);
}

TEST_F(MackieServiceImplTest, GetsMultipleMIDIDevicesFromMIDIService)
{
	using ::testing::Return;
	std::vector<int> input = {5, 6};

	MIDIDeviceMock midiDevice1;
	MIDIDevice* midiDeviceRef1 = &midiDevice1;

	MIDIDeviceMock midiDevice2;
	MIDIDevice* midiDeviceRef2 = &midiDevice2;

	EXPECT_CALL(*midiService, GetMIDIDeviceProxy(input[1])).Times(1).WillOnce(Return(midiDeviceRef1));
	EXPECT_CALL(*midiService, GetMIDIDeviceProxy(input[0])).Times(1).WillOnce(Return(midiDeviceRef2));

	instance->GetMackieComposite(input);
}

TEST_F(MackieServiceImplTest, CreatesCompositeCorrectly)
{
	using ::testing::Return;
	std::vector<int> input = {5};

	MIDIDeviceMock midiDevice;
	MIDIDevice* midiDeviceRef = &midiDevice;

	MackieDeviceMock mackieDevice;
	MackieDevice* mackieDeviceRef = &mackieDevice;
	std::vector<MackieDevice*> mackieDevicePtrs = {mackieDeviceRef};

	MackieCompositeMock mackieComposite;
	MackieComposite* mackieCompositeRef = &mackieComposite;

	EXPECT_CALL(*midiService, GetMIDIDeviceProxy(input[0])).Times(1).WillOnce(Return(midiDeviceRef));
	EXPECT_CALL(*mackieDeviceFactory, CreateProxy(midiDeviceRef)).Times(1).WillOnce(Return(mackieDeviceRef));
	EXPECT_CALL(*mackieCompositeFactory, CreateProxy(mackieDevicePtrs)).Times(1).WillOnce(Return(mackieCompositeRef));

	auto actual = instance->GetMackieComposite(input);

	EXPECT_NE(nullptr, actual.get());
	EXPECT_EQ(mackieCompositeRef, actual.get());
}