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
		static double LinearToMotu(double linearValue);

		/// Converts a non-linear MOTU value to a linear value.
		static double MotuToLinear(double motuValue);

		static int LinearToInteger10bit(double linearValue);

		static double Integer10bitToLinear(int integer10bit);

		static std::array<unsigned char, 2> Integer10bitToMackie(int integer10bit);

		static int MackieToInteger10bit(std::array<unsigned char, 2> mackie);
	};
}

#endif // MACKIE_OF_THE_UNICORN_FADERVALUECONVERTER_H
