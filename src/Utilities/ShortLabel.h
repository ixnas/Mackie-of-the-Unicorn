//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_SHORTLABEL_H
#define MACKIE_OF_THE_UNICORN_SHORTLABEL_H

#include <string>

namespace MackieOfTheUnicorn::Utilities
{
	class ShortLabel
	{
		char OutputLabel[7];

	  public:
		explicit ShortLabel(std::string_view inputLabel);
		std::string_view Get();
	};
}

#endif // MACKIE_OF_THE_UNICORN_SHORTLABEL_H
