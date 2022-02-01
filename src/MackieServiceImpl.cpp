//
// Created by Sjoerd Scheffer on 01/02/2022.
//

#include "MackieServiceImpl.h"
#include "MackieComposite.h"
#include <vector>

std::map<int, std::string> MackieServiceImpl::GetDevices()
{
	return {};
}

std::unique_ptr<MackieComposite> MackieServiceImpl::GetMackieComposite(std::vector<int> deviceIds)
{
	return {};
}
