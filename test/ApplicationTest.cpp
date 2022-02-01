//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/Application.h"
#include "../src/MackieService.h"
#include "../src/MackieComposite.h"

typedef std::map<int, std::string> GetDevicesRet;
typedef std::vector<int> GetMackieCompositeArg;
typedef std::unique_ptr<MackieComposite> GetMackieCompositeRet;

class MockMackieService : public MackieService
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
		mockMackieService = std::make_unique<MockMackieService>();
		instance = std::make_unique<Application>(*mockMackieService);
	}

	std::unique_ptr<MockMackieService> mockMackieService;
	std::unique_ptr<Application> instance;
};

TEST_F(ApplicationTest, GetAvailableDevicesReturnsProperList) {
	using ::testing::Return;
	GetDevicesRet input = {
	    {
	        0,
	        "test1"
	    },
	    {
	        1,
	        "test2"
	    }
	};
	auto expected = "Available devices:\n0: test1\n1: test2\n";

	EXPECT_CALL(*mockMackieService, GetDevices())
	    .Times(1)
	    .WillOnce(Return(input));

	auto actual = instance->GetAvailableDevices();

	EXPECT_STREQ(expected, actual.c_str());
}

TEST_F(ApplicationTest, GetAvailableDevicesReturnsEmpty) {
	using ::testing::Return;
	GetDevicesRet input = {};
	auto expected = "No available devices.\n";

	EXPECT_CALL(*mockMackieService, GetDevices())
		.Times(1)
		.WillOnce(Return(input));

	auto actual = instance->GetAvailableDevices();

	EXPECT_STREQ(expected, actual.c_str());
}
