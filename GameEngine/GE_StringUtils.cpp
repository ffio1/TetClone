#include "stdafx.h"
#include "GE_StringUtils.h"

static std::string locEmptyString = std::string("");

//--------------------------------------------------------------------------------
const std::string& GE_StringUtils::GetEmptyString()
{
	return locEmptyString;
}