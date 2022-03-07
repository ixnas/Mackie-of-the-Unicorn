//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_ETAGPARSER_H
#define MACKIE_OF_THE_UNICORN_ETAGPARSER_H

namespace MackieOfTheUnicorn::HTTP
{
	/// Parses a string of headers and returns the ETag if it's present.
	class ETagParser
	{
	  public:
		/// Returns the ETag as a value, or nothing if there isn't any.
		static std::optional<int> GetETag(std::string headers);
	};
}

#endif // MACKIE_OF_THE_UNICORN_ETAGPARSER_H
