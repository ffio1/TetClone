#pragma once
#include "GE_Application.h"

class TetClient_Application : public GE_Application
{
public:
	TetClient_Application(const std::vector<std::string>& someArguments);

	void Update() override;

private:
	void Init();

	// Block manager
	// Etc
};