//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "../src/Application.h"
#include "../src/MackieComposite.h"
#include "../src/MackieService.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MackieServiceMock : public MackieService
{
  public:
	MOCK_METHOD((std::map<int, std::string>), GetInputDevices, (), (override));
	MOCK_METHOD((std::map<int, std::string>), GetOutputDevices, (), (override));
	MOCK_METHOD(std::unique_ptr<MackieComposite>, GetMackieComposite, ((const std::vector<std::pair<int, int>>&)), (override));
};

class ApplicationTest : public ::testing::Test
{
  protected:
	void SetUp() override
	{
		mackieServiceMock = std::make_unique<MackieServiceMock>();
		instance = std::make_unique<Application>(*mackieServiceMock);
	}

	std::unique_ptr<MackieServiceMock> mackieServiceMock;
	std::unique_ptr<Application> instance;
};

TEST_F(ApplicationTest, GetAvailableInputDevicesReturnsProperList)
{
	using ::testing::Return;
	std::map<int, std::string> expected = {{0, "test1"}, {1, "test2"}};

	EXPECT_CALL(*mackieServiceMock, GetInputDevices()).Times(1).WillOnce(Return(expected));

	auto actual = instance->GetAvailableInputDevices();

	EXPECT_EQ(expected, actual);
}

TEST_F(ApplicationTest, GetAvailableOutputDevicesReturnsProperList)
{
	using ::testing::Return;
	std::map<int, std::string> expected = {{0, "test1"}, {1, "test2"}};

	EXPECT_CALL(*mackieServiceMock, GetOutputDevices()).Times(1).WillOnce(Return(expected));

	auto actual = instance->GetAvailableOutputDevices();

	EXPECT_EQ(expected, actual);
}
