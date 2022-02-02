//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "../src/Application.h"
#include "../src/MackieComposite.h"
#include "../src/MackieService.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

typedef std::map<int, std::string> GetDevicesRet;
typedef std::vector<int> GetMackieCompositeArg;
typedef std::unique_ptr<MackieComposite> GetMackieCompositeRet;

class MackieServiceMock : public MackieService
{
  public:
	MOCK_METHOD(GetDevicesRet, GetDevices, (), (override));
	MOCK_METHOD(GetMackieCompositeRet, GetMackieComposite, (GetMackieCompositeArg), (override));
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

TEST_F(ApplicationTest, GetAvailableDevicesReturnsProperList)
{
	using ::testing::Return;
	GetDevicesRet expected = {{0, "test1"}, {1, "test2"}};

	EXPECT_CALL(*mackieServiceMock, GetDevices()).Times(1).WillOnce(Return(expected));

	auto actual = instance->GetAvailableDevices();

	EXPECT_EQ(expected, actual);
}
