//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H

#include "../src/MackieDevice.h"

class MackieDeviceFake : public MackieDevice
{
  public:
	int Position = 0;
	std::string Text;

	void SetText(int position, std::string text) override
	{
		this->Position = position;
		this->Text = text;
	}
};

#endif // MACKIE_OF_THE_UNICORN_MACKIEDEVICEFAKE_H
