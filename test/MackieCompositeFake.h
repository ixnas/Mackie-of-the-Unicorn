//
// Created by Sjoerd Scheffer on 04/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
#define MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H

#include "../src/MackieComposite.h"
#include <vector>
#include <string>

class MackieCompositeFake : public MackieComposite
{
  public:
	std::vector<std::unique_ptr<MackieDevice>> Devices;
	int Position = 0;
	std::string Text;

	void AddMackieDevice(std::unique_ptr<MackieDevice> device) override
	{
		Devices.push_back(std::move(device));
	}

	void SetText(int position, std::string text) override
	{
		this->Position = position;
		this->Text = text;
	}
};

#endif // MACKIE_OF_THE_UNICORN_MACKIECOMPOSITEFAKE_H
