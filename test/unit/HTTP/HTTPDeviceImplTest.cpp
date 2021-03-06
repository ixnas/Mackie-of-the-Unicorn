//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "gtest/gtest.h"
#include "../../../src/HTTP/HTTPDeviceImpl.h"
#include "../../fakes/LibraryAbstractions/Curl/CurlAbstractionFake.h"
#include "../../fakes/HTTP/HTTPListenerFake.h"

namespace MackieOfTheUnicorn::Tests::Unit::HTTP
{
	class HTTPDeviceImplTest : public ::testing::Test
	{
	  protected:
		void SetUp() override
		{
			httpListenerFake = std::make_unique<MackieOfTheUnicorn::HTTP::HTTPListenerFake>();
			auto curlInPtr = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionFake>();
			auto curlOutPtr = std::make_unique<MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionFake>();

			curlIn = curlInPtr.get();
			curlOut = curlOutPtr.get();

			instance = std::make_unique<MackieOfTheUnicorn::HTTP::HTTPDeviceImpl>(std::move(curlInPtr), std::move(curlOutPtr));
			instance->RegisterCallback(*httpListenerFake);
		}

		std::unique_ptr<MackieOfTheUnicorn::HTTP::HTTPListenerFake> httpListenerFake;
		MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionFake* curlIn;
		MackieOfTheUnicorn::LibraryAbstractions::Curl::CurlAbstractionFake* curlOut;
		std::unique_ptr<MackieOfTheUnicorn::HTTP::HTTPDeviceImpl> instance;
	};

	TEST_F(HTTPDeviceImplTest, SendMessageSendsMessage)
	{
		std::string key1 = "key1";
		JSON::JSONValue value1;
		value1.Integer = 128;

		std::pair<std::string, JSON::JSONValue> message = {key1, value1};

		auto expectedMessage1 = "json={\"key1\":128}";
		instance->SendMessage(message);
		auto actualMessage1 = curlOut->SetPostDataPostData;

		EXPECT_EQ(actualMessage1, expectedMessage1);
	}

	TEST_F(HTTPDeviceImplTest, NoChangeDoesntCallCallback)
	{
		curlIn->FakeNoneChangedMessage();
		instance->StartListening();
		instance->StopListening();

		EXPECT_TRUE(httpListenerFake->Messages.empty());
	}

	TEST_F(HTTPDeviceImplTest, ChangeCallsCallback)
	{
		curlIn->FakeHasChangedMessage("{\"key1\":128}");
		instance->StartListening();
		instance->StopListening();

		EXPECT_FALSE(httpListenerFake->Messages.empty());

		auto lastMessage = *(httpListenerFake->Messages.end() - 1);

		std::string expectedLastMessageKey = "key1";
		int expectedLastMessageValue = 128;

		auto actualLastMessageKey = lastMessage.first;
		auto actualLastMessageValue = lastMessage.second.Integer.value();

		EXPECT_EQ(actualLastMessageKey, expectedLastMessageKey);
		EXPECT_EQ(actualLastMessageValue, expectedLastMessageValue);
	}

	TEST_F(HTTPDeviceImplTest, UsesETagAfterFirstRound)
	{
		curlIn->FakeHasChangedMessage("{\"key1\":128}");
		instance->StartListening();
		curlIn->FakeHasChangedMessage("{\"key1\":127}");

		auto start = std::chrono::system_clock::now();
		while (!curlIn->SetHeadersHeaders.has_value())
		{
			auto end = std::chrono::system_clock::now();
			auto diff = start - end;
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
			if (duration > 0)
			{
				FAIL() << "Headers didn't get set.";
			}
		}
		instance->StopListening();

		auto hasSetHeaders = curlIn->SetHeadersHeaders.has_value();

		EXPECT_TRUE(hasSetHeaders);
	}

	TEST_F(HTTPDeviceImplTest, AbortsCurlWhenDeconstructing)
	{
		curlIn->FakeHasChangedMessage("{\"key1\":128}");
		instance->StartListening();

		instance.reset();

		auto abortCalled = curlIn->AbortCalled;

		EXPECT_TRUE(abortCalled);
	}
} // namespace MackieOfTheUnicorn::Tests::Unit::HTTP