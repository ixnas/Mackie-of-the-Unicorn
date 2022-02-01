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

TEST(ApplicationTest, GetAvailableDevicesReturnsProperList) {
	using ::testing::Return;
	MockMackieService mockMackieService;
	Application app(mockMackieService);
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
	EXPECT_CALL(mockMackieService, GetDevices())
	    .Times(1)
	    .WillOnce(Return(input));
	auto expected = "Available devices:\n0: test1\n1: test2\n";
	auto actual = app.GetAvailableDevices();
	// Expect two strings not to be equal.
	EXPECT_STREQ(expected, actual.c_str());
}
