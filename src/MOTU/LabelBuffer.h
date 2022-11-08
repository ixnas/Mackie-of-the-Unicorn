//
// Created by Sjoerd Scheffer on 06/11/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_LABELBUFFER_H
#define MACKIE_OF_THE_UNICORN_LABELBUFFER_H

#include "../JSON/JSONValue.h"

namespace MackieOfTheUnicorn::MOTU
{
	/// Stores JSON messages related to I/O labels until there's enough information to label input channels.
	class LabelBuffer
	{
		std::vector<std::pair<std::vector<std::string>, JSON::JSONValue>> CachedMessages;
		std::optional<int> ObankNumber;
		std::map<int, std::string> DefaultChannelLabels;
		std::map<int, std::string> CachedChannelLabels;

		void SetObankNumber(std::pair<std::vector<std::string>, JSON::JSONValue>& message);
		void MoveCachedKeyValuePairsToMaps();
		std::map<int, std::string> GetUnsetLabelsFromCache();
	  public:
		LabelBuffer() = default;

		/// Attempts to return labels that haven't been set yet while processing the specified message. The map index maps to an input channel number.
		std::map<int, std::string> GetLabels(std::pair<std::vector<std::string>, JSON::JSONValue>& message);
	};
}

#endif // MACKIE_OF_THE_UNICORN_LABELBUFFER_H
