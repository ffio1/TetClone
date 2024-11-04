#pragma once

class GE_Application
{
public:
	GE_Application(const std::string& anApplicationName, const std::vector<std::string>& someArguments);
	~GE_Application() = default;

public:
	const std::string& GetApplicationName() const { return myApplicationName; }
	const std::string& GetArgument(int anArgumentIndex) const;

protected:
	virtual void Update();

private:
	std::string myApplicationName;
	std::vector<std::string> myArguments;

	// Renderer Backend (modular, DX12, Vulkan, etc.?)
	// Settings Manager
	// Input Manager
	// ImGUI Manager
	// Asset Manager
	// Etc.
};