//
// Created by Sjoerd Scheffer on 06/03/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_SHORTLABEL_H
#define MACKIE_OF_THE_UNICORN_SHORTLABEL_H

namespace MackieOfTheUnicorn::Utilities
{
	/// Represents a version of a string that fits into a scribble strip on a Mackie control surface.
	class ShortLabel
	{
	  public:
		static constexpr int MAX_LENGTH = 6;
	  private:
		char OutputLabel[MAX_LENGTH + 1];

	  public:
		explicit ShortLabel(std::string_view inputLabel);

		/// Returns the generated label.
		std::string_view Get();
	};
}

#endif // MACKIE_OF_THE_UNICORN_SHORTLABEL_H
