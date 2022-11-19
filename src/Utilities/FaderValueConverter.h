//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H
#define MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H

namespace MackieOfTheUnicorn::Utilities
{
	/// Converts between non-linear values from the MOTU API and a linear values between 0 and 1.
	class FaderValueConverter
	{
	  public:
		/// Converts a linear value to a non-linear MOTU value.
		static double ToMotu(double linearValue);

		/// Converts a non-linear MOTU value to a linear value.
		static double ToLinear(double motuValue);

		static int To10bitInteger(double linearValue);

		static std::array<unsigned char, 2> ToSplit10BitInteger(int integer10bit);
	};
}

#endif // MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H
