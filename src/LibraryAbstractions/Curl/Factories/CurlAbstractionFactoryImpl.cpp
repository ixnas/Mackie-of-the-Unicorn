//
// Created by Sjoerd Scheffer on 19/02/2022.
//

#include "CurlAbstractionFactoryImpl.h"
#include "../CurlAbstractionImpl.h"

namespace MackieOfTheUnicorn::LibraryAbstractions::Curl::Factories
{
	std::unique_ptr<Curl::CurlAbstraction> CurlAbstractionFactoryImpl::Create()
	{
		return std::make_unique<Curl::CurlAbstractionImpl>();
	}
}
