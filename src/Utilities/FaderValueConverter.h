//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H
#define MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H

namespace MackieOfTheUnicorn::Utilities
{
	class FaderValueConverter
	{
	  public:
		static double ToMotu(double linearValue);
		static double ToLinear(double motuValue);
	};
}

#endif // MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H
