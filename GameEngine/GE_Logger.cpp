#include "stdafx.h"
#include "GE_Logger.h"

#include <iostream>
#include <iomanip>

typedef std::chrono::system_clock GE_Logger_ClockType;

static constexpr const char* locMessageTypeStr[static_cast<unsigned int>(GE_Logger::LogMessageType::Count)]
{
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR",
	"CRITICAL"
};

static constexpr const char* locLogTimestampFormat = "%Y-%m-%dT%H:%S:%MZ";

//--------------------------------------------------------------------------------
GE_Logger::LogMessage::LogMessage(LogMessageType aType, const std::string& aMessage, const std::string& aLocation, std::time_t aTime)
	: myType(aType)
	, myMessage(aMessage)
	, myLocation(aLocation)
	, myTime(aTime)
{
}

//--------------------------------------------------------------------------------
std::string GE_Logger::LogMessage::FormatLogMessage(const std::string& aFormat, ...)
{
	static constexpr int bufferSize = 256;
	char logMessageBuffer[bufferSize] = "";

	va_list args;
	va_start(args, &aFormat);

	vsprintf_s(logMessageBuffer, bufferSize, aFormat.c_str(), args);

	va_end(args);

	return std::string(logMessageBuffer);
}

//--------------------------------------------------------------------------------
void GE_Logger::LogMessage::Print() const
{
	static constexpr int timeBufferSize = 32;
	char timeBuffer[timeBufferSize];
	tm tm;
	errno_t timeError = localtime_s(&tm, &myTime);

	if (timeError == 0)
	{
		strftime(timeBuffer, timeBufferSize, "%Y-%m-%dT%H:%S:%MZ", &tm);
	}
	else
	{
		std::string timeStr = std::to_string(myTime);
		strcpy_s(timeBuffer, timeStr.size(), std::to_string(myTime).c_str());
	}
	
	// time [type] Where | Messagez
	printf_s("%s\t[%s]  \t%s\t| %s\n",
		timeBuffer,
		locMessageTypeStr[static_cast<unsigned int>(myType)],
		myLocation.c_str(),
		myMessage.c_str());
}

//--------------------------------------------------------------------------------
GE_Logger::GE_Logger()
{
	myLogStartTime = std::chrono::system_clock::to_time_t(GE_Logger_ClockType::now());
}

//--------------------------------------------------------------------------------
void GE_Logger::AddLogMessage(LogMessageType aType, const std::string& aMessage, const std::string& aLocation)
{
	std::time_t currentTime = std::chrono::system_clock::to_time_t(GE_Logger_ClockType::now());
	return AddLogMessage(LogMessage(aType, aMessage, aLocation, currentTime));
}

//--------------------------------------------------------------------------------
void GE_Logger::AddLogMessage(const LogMessage& aLogMessage)
{
	std::lock_guard<std::mutex> guard(myMessageMutex);

	myPendingLogMessages.push(aLogMessage);
}

//--------------------------------------------------------------------------------
void GE_Logger::PrintAllPendingMessages()
{
	std::lock_guard<std::mutex> guard(myMessageMutex);

	while (!myPendingLogMessages.empty())
	{
		LogMessage& message = myPendingLogMessages.front();
		message.Print();
		myPendingLogMessages.pop();
	}
}