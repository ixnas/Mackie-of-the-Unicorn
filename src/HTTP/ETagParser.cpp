//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#include "ETagParser.h"

namespace MackieOfTheUnicorn::HTTP
{
	std::optional<int> ETagParser::GetETag(std::string headers)
	{
		static const std::string DELIMITER = "\r\n";
		static const auto etagLength = strlen("ETag: ");

		auto etagHeaderNameIndex = headers.find("ETag: ");

		if (etagHeaderNameIndex == std::string::npos)
		{
			return {};
		}

		auto etagIndex = etagHeaderNameIndex + etagLength;

		auto fromEtagToEnd = headers.substr(etagIndex);
		auto delimiterIndex = headers.find("\r\n");
		auto etagString = fromEtagToEnd.substr(0, delimiterIndex);

		return std::stoi(etagString);
	}
}