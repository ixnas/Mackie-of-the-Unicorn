//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "FaderValueConverter.h"

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

	int FaderValueConverter::To10bitInteger(double linearValue)
	{
		return (int)(linearValue * (double)1024);
	}

	std::array<unsigned char, 2> FaderValueConverter::ToSplit10BitInteger(int integer10bit)
	{
		return {(unsigned char)(integer10bit & 0x7F), (unsigned char)(integer10bit >> 3)};
	}
}
