//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H

#include <string>

namespace MackieOfTheUnicorn::Mackie
{
	class MackieDevice;

	class MackieComposite
	{
	  public:
		virtual ~MackieComposite() = default;
		virtual void AddMackieDevice(std::unique_ptr<MackieDevice> mackieDevice) = 0;
		virtual void SetText(int position, std::string text) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITE_H
