#include "stdafx.h"
#include "TetClient_Application.h"

namespace
{
	static const std::string locApplicationName = std::string("TetClone");
}

//--------------------------------------------------------------------------------
TetClient_Application::TetClient_Application(const std::vector<std::string>& someArguments)
	: GE_Application(locApplicationName, someArguments)
{
	Init();
}

//--------------------------------------------------------------------------------
void TetClient_Application::Init()
{
	GE_LOG_DEBUG("This is a test DEBUG message! %s", "Test1");
	GE_LOG_INFO("This is a test INFO message! %d", 2);
	GE_LOG_WARNING("This is a test WARNING message! %f", 3.25f);
	GE_LOG_ERROR("This is a test INFO message! %i", 4002);
	GE_LOG_CRITICAL("This is a test INFO message! %s %s", "Multiple strings!", "Times two!");
}

//--------------------------------------------------------------------------------
void TetClient_Application::Update()
{
	GE_Application::Update();

	GE_Logger::GetInstance().PrintAllPendingMessages();
}