//
// Created by Sjoerd Scheffer on 06/11/2022.
//

#include "LabelCache.h"
#include "../JSON/JSONValue.h"

namespace MackieOfTheUnicorn::MOTU
{
	enum class LabelType
	{
		NONE,
		OBANK_NAME,
		DEFAULT_INPUT_NAME,
		INPUT_NAME,
	};

	static LabelType GetLabelType(const std::pair<std::vector<std::string>, JSON::JSONValue>& message)
	{
		auto keyParts = message.first;
		auto value = message.second;

		if (keyParts.size() < 4 || keyParts[0] != "ext" || keyParts[1] != "obank")
		{
			return LabelType::NONE;
		}

		if (keyParts[3] == "name" && value.String.has_value() && value.String.value() == "Mix In")
		{
			return LabelType::OBANK_NAME;
		}

		if (keyParts.size() < 6)
		{
			return LabelType::NONE;
		}

		if (keyParts[5] == "defaultName")
		{
			return LabelType::DEFAULT_INPUT_NAME;
		}

		if (keyParts[5] == "name")
		{
			return LabelType::INPUT_NAME;
		}

		return LabelType::NONE;
	}

	std::map<int, std::string> LabelCache::GetLabels(std::pair<std::vector<std::string>, JSON::JSONValue>& message)
	{
		auto labelType = GetLabelType(message);
		if (labelType == LabelType::NONE)
		{
			return {};
		}

		if (labelType == LabelType::OBANK_NAME)
		{
			SetObankNumber(message);
			MoveCachedKeyValuePairsToMaps();
			return GetUnsetLabelsFromCache();
		}

		if (!ObankNumber.has_value())
		{
			CachedMessages.push_back(message);
			return {};
		}

		auto channelNumber = std::stoi(message.first[4]);
		auto name = message.second.String.value();

		if (labelType == LabelType::DEFAULT_INPUT_NAME)
		{
			DefaultChannelLabels.insert({channelNumber, name});
		}
		else
		{
			CachedChannelLabels.insert_or_assign(channelNumber, name);
		}

		return GetUnsetLabelsFromCache();
	}

	void LabelCache::SetObankNumber(std::pair<std::vector<std::string>, JSON::JSONValue>& message)
	{
		auto obankNumberString = message.first[2];
		ObankNumber = std::stoi(obankNumberString);
	}

	void LabelCache::MoveCachedKeyValuePairsToMaps()
	{
		for (const auto& message : CachedMessages)
		{
			auto channelNumber = std::stoi(message.first[4]);
			auto name = message.second.String.value();

			auto labelType = GetLabelType(message);
			if (labelType == LabelType::DEFAULT_INPUT_NAME)
			{
				DefaultChannelLabels.insert({channelNumber, name});
				continue;
			}

			CachedChannelLabels.insert({channelNumber, name});
		}

		CachedMessages = std::vector<std::pair<std::vector<std::string>, JSON::JSONValue>>();
	}

	std::map<int, std::string> LabelCache::GetUnsetLabelsFromCache()
	{
		std::map<int, std::string> unsetLabels;

		for (auto i = 0; i < 48; i++)
		{
			auto hasDefaultLabel = DefaultChannelLabels.contains(i);
			auto hasLabel = CachedChannelLabels.contains(i);

			if (!hasLabel || !hasDefaultLabel)
			{
				continue;
			}

			auto label = CachedChannelLabels[i];
			auto defaultLabel = DefaultChannelLabels[i];

			if (label.empty())
			{
				unsetLabels.insert({i, defaultLabel});
			}
			else
			{
				unsetLabels.insert({i, label});
			}

			CachedChannelLabels.erase(i);
		}

		return unsetLabels;
	}
}