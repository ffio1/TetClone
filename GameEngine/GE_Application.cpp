#include "stdafx.h"
#include "GE_Application.h"

//--------------------------------------------------------------------------------
GE_Application::GE_Application(const std::string& anApplicationName, const std::vector<std::string>& someArguments)
	: myApplicationName(anApplicationName)
	, myArguments(someArguments)
	, myD2DApplication(anApplicationName, anApplicationName, Core_Vector2i(640, 480))
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
void GE_Application::Init()
{
	myD2DApplication.Initialize();
}

//--------------------------------------------------------------------------------
void GE_Application::Update()
{
	myD2DApplication.Update();
}