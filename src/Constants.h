//
// Created by Sjoerd Scheffer on 12/11/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_CONSTANTS_H
#define MACKIE_OF_THE_UNICORN_CONSTANTS_H

namespace MackieOfTheUnicorn
{
	/// Provides access to global compile-time constants.
	class Constants
	{
	  public:

		/// Returns a string containing the licenses for the application and its used libraries.
		static std::string_view GetLicenses();

		/// Returns the current version as either a version number or short commit hash.
		static std::string_view GetVersion();

		/// Returns the current year.
		static std::string_view GetYear();
	};
}

#endif // MACKIE_OF_THE_UNICORN_CONSTANTS_H
