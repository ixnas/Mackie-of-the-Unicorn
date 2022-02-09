//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H

#include <string>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;

	/// Provides an interface to communicatie with a group of Mackie controllers.
	class MackieComposite
	{
	  public:
		virtual ~MackieComposite() = default;
		virtual void SetText(int position, std::string text) = 0;
	};
} // namespace MackieOfTheUnicorn::Mackie

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
