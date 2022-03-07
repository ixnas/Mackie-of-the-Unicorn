//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_JSONSERIALIZER_H
#define MACKIE_OF_THE_UNICORN_JSONSERIALIZER_H

namespace MackieOfTheUnicorn::JSON
{
	class JSONValue;

	/// Serializes or de-serializes flat json documents.
	class JSONSerializer
	{
	  public:
		/// Parses a string and returns key/value pairs.
		static std::vector<std::pair<std::string, JSONValue>> Parse(std::string& string);

		/// Serializes a string to key/value pairs.
		static std::string Serialize(std::vector<std::pair<std::string, JSONValue>>& object);
	};
}

#endif // MACKIE_OF_THE_UNICORN_JSONSERIALIZER_H
