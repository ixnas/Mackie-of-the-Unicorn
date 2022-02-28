//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_MACKIEVIEW_H
#define MACKIE_OF_THE_UNICORN_MACKIEVIEW_H

#include "../Mixers/Mixer.h"
#include "../Mackie/MackieListener.h"
#include "../Mackie/MackieComposite.h"

namespace MackieOfTheUnicorn
{
	class MackieView : public Mixers::Mixer, public Mackie::MackieListener<Mackie::MackieComposite>
	{
	};
}

#endif // MACKIE_OF_THE_UNICORN_MACKIEVIEW_H
