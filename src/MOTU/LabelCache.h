//
// Created by Sjoerd Scheffer on 06/11/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LABELCACHE_H
#define MACKIE_OF_THE_UNICORN_LABELCACHE_H

#include "../JSON/JSONValue.h"

namespace MackieOfTheUnicorn::MOTU
{
	class LabelCache
	{
		std::vector<std::pair<std::vector<std::string>, JSON::JSONValue>> CachedMessages;
		std::optional<int> ObankNumber;
		std::map<int, std::string> DefaultChannelLabels;
		std::map<int, std::string> CachedChannelLabels;

		void SetObankNumber(std::pair<std::vector<std::string>, JSON::JSONValue>& message);
		void MoveCachedKeyValuePairsToMaps();
		std::map<int, std::string> GetUnsetLabelsFromCache();
	  public:
		LabelCache() = default;
		std::map<int, std::string> GetLabels(std::pair<std::vector<std::string>, JSON::JSONValue>& message);
	};
}

#endif // MACKIE_OF_THE_UNICORN_LABELCACHE_H
