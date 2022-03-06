//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "FaderValueConverter.h"
#include <cmath>

namespace MackieOfTheUnicorn::Utilities
{
	double FaderValueConverter::ToMotu(double linearValue)
	{
		return 4 * pow(linearValue, 4);
	}

	double FaderValueConverter::ToLinear(double motuValue)
	{
		return pow((motuValue / 4.0), 1.0 / 4.0);
	}
}
