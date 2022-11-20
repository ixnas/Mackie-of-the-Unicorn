//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#include "FaderValueConverter.h"

namespace MackieOfTheUnicorn::Utilities
{
	double FaderValueConverter::LinearToMotu(double linearValue)
	{
		return 4 * pow(linearValue, 4);
	}

	double FaderValueConverter::MotuToLinear(double motuValue)
	{
		return pow((motuValue / 4.0), 1.0 / 4.0);
	}

	int FaderValueConverter::LinearToInteger10bit(double linearValue)
	{
		return (int)(linearValue * (double)1023);
	}

	double FaderValueConverter::Integer10bitToLinear(int integer10bit)
	{
		return (double)1.0 / 0x3FF * integer10bit;
	}

	std::array<unsigned char, 2> FaderValueConverter::Integer10bitToMackie(int integer10bit)
	{
		return {(unsigned char)(integer10bit & 0x7F), (unsigned char)(integer10bit >> 3)};
	}

	int FaderValueConverter::MackieToInteger10bit(std::array<unsigned char, 2> mackie)
	{
		return ((mackie[1] << 3 & 0x3F0) | mackie[0]);
	}
}
