#include "stdafx.h"
#include "GE_Application.h"

//--------------------------------------------------------------------------------
GE_Application::GE_Application(const std::string& anApplicationName, const std::vector<std::string>& someArguments)
	: myApplicationName(anApplicationName)
	, myArguments(someArguments)
{
}

//--------------------------------------------------------------------------------
const std::string& GE_Application::GetArgument(int anArgumentIndex) const
{
	if (anArgumentIndex < 0 || anArgumentIndex >= myArguments.size())
	{
		return GE_StringUtils::GetEmptyString();
	}

	return myArguments.at(anArgumentIndex);
}

//--------------------------------------------------------------------------------
void GE_Application::Update()
{
}