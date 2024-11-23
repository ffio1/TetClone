#include "stdafx.h"
#include "GE_StringUtils.h"

//--------------------------------------------------------------------------------
const std::string& GE_StringUtils::GetEmptyString()
{
	static const std::string emptyString = std::string("");

	return emptyString;
}