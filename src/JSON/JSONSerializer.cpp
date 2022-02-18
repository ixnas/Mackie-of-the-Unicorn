//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#include "JSONSerializer.h"
#include "JSONValue.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

namespace MackieOfTheUnicorn::JSON
{
	std::vector<std::pair<std::string, JSONValue>> JSONSerializer::Parse(std::string& string)
	{
		rapidjson::Document document;
		document.Parse(string.c_str());

		std::vector<std::pair<std::string, MackieOfTheUnicorn::JSON::JSONValue>> pairs;
		pairs.resize(document.MemberCount());

		int i = 0;
		for (auto iterator = document.MemberBegin(); iterator != document.MemberEnd(); iterator++)
		{
			pairs[i].first = iterator->name.GetString();
			if (iterator->value.IsInt())
			{
				pairs[i].second.Integer = iterator->value.GetInt();
			}
			else if (iterator->value.IsFloat())
			{
				pairs[i].second.Float = iterator->value.GetFloat();
			}
			else if (iterator->value.IsString())
			{
				pairs[i].second.String = iterator->value.GetString();
			}
			i++;
		}

		return pairs;
	}

	std::string JSONSerializer::Serialize(std::vector<std::pair<std::string, JSONValue>>& object)
	{
		rapidjson::Document document;
		document.SetObject();
		auto allocator = document.GetAllocator();

		for (const auto& message : object)
		{
			auto key = message.first;
			auto value = message.second;

			auto stringKey = key.c_str();
			auto stringKeyLength = key.length();
			rapidjson::Value jsonKey;
			jsonKey.SetString(stringKey, stringKeyLength, allocator);

			rapidjson::Value jsonValue;

			if (value.Integer.has_value())
			{
				auto intValue = value.Integer.value();
				jsonValue.SetInt(intValue);
			}
			else if (value.Float.has_value())
			{
				auto floatValue = value.Float.value();
				jsonValue.SetFloat(floatValue);
			}
			else if (value.String.has_value())
			{
				auto stringValue = value.String.value().c_str();
				auto stringValueLength = value.String.value().length();
				jsonValue.SetString(stringValue, stringValueLength, allocator);
			}
			else
			{
				continue;
			}
			document.AddMember(jsonKey, jsonValue, allocator);
		}

		rapidjson::StringBuffer stringBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
		document.Accept(writer);
		return stringBuffer.GetString();
	}
}