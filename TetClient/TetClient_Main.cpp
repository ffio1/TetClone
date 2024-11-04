#include "stdafx.h"
#include "TetClient_Main.h"

#include "TetClient_Application.h"

//--------------------------------------------------------------------------------
void GetArguments(std::vector<std::string>& someOutArguments)
{
	someOutArguments.clear();

	int argc = __argc;
	char** argv = __argv;

	someOutArguments.resize(argc);

	for (int i = 0; i < argc; i++)
	{
		someOutArguments.emplace_back(argv[i]);
	}
}

#if ENABLE_CONSOLE_LOGS
//--------------------------------------------------------------------------------
void InitializeLogging()
{
	BOOL consoleAllocated = AllocConsole();
	if (!consoleAllocated)
	{
		return;
	}

	FILE* outputBuffer;
	freopen_s(&outputBuffer, "CONOUT$", "w", stdout);
	SetConsoleTitle(L"TetClient Console");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}
#endif // ENABLE_CONSOLE_LOGS

//--------------------------------------------------------------------------------
int CALLBACK WinMain(
	_In_ HINSTANCE anInstance,
	_In_opt_ HINSTANCE aPreviousInstance,
	_In_ LPSTR aCommandLine,
	_In_ int aShowCommand
)
{
#if ENABLE_CONSOLE_LOGS
	InitializeLogging();
#endif // ENABLE_CONSOLE_LOGS

	std::vector<std::string> args;
	GetArguments(args);

	TetClient_Application application = TetClient_Application(args);

	// TODO: When input manager is created, add a condition where this may end due to
	// an input event (ex: clicking x in top right)
	while (true)
	{
		application.Update();


		// TODO: Update when we add some sort of FPS cap.
		// Should be based off frame timings.
		Sleep(10);
	}

	return 0;
}