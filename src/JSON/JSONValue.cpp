//
// Created by Sjoerd Scheffer on 18/02/2022.
//

#include "JSONValue.h"

namespace MackieOfTheUnicorn::JSON
{
	bool JSONValue::operator==(const JSONValue& object) const
	{
		return this->String == object.String && this->Integer == object.Integer && this->Float == object.Float;
	}
} // namespace MackieOfTheUnicorn::JSON