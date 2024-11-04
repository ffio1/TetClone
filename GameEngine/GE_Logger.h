#pragma once

#include <chrono>
#include <cstdarg>
#include <mutex>
#include <queue>

#include "GE_SimpleSingleton.h"

class GE_Logger : public GE_SimpleSingleton<GE_Logger>
{
public:
	enum class LogMessageType
	{
		Debug,
		Info,
		Warning,
		Error,
		Critical,
		Count
	};

	struct LogMessage
	{
		LogMessage(LogMessageType aType, const std::string& aMessage, const std::string& aLocation, std::time_t aTime);

		static std::string FormatLogMessage(const std::string& aFormat, ...);

		void Print() const;

		LogMessageType myType;
		std::string myMessage;
		std::string myLocation;
		std::time_t myTime;
	};

public:
	GE_Logger();

public:
	void AddLogMessage(LogMessageType aType, const std::string& aMessage, const std::string& aLocation);
	void AddLogMessage(const LogMessage& aMessage);
	void PrintAllPendingMessages();

private:
	std::mutex myMessageMutex;
	std::queue<LogMessage> myPendingLogMessages;
	std::time_t myLogStartTime;
};

#define GE_LOG_GENERIC(TYPE, FORMAT, ...) GE_Logger::GetInstance().AddLogMessage( \
TYPE, \
GE_Logger::LogMessage::FormatLogMessage(FORMAT, __VA_ARGS__), \
GE_Logger::LogMessage::FormatLogMessage("%s (line: %d)", __FUNCTION__, __LINE__) \
)

#define GE_LOG_DEBUG(FORMAT, ...) GE_LOG_GENERIC(GE_Logger::LogMessageType::Debug, FORMAT, __VA_ARGS__)
#define GE_LOG_INFO(FORMAT, ...) GE_LOG_GENERIC(GE_Logger::LogMessageType::Info, FORMAT, __VA_ARGS__)
#define GE_LOG_WARNING(FORMAT, ...) GE_LOG_GENERIC(GE_Logger::LogMessageType::Warning, FORMAT, __VA_ARGS__)
#define GE_LOG_ERROR(FORMAT, ...) GE_LOG_GENERIC(GE_Logger::LogMessageType::Error, FORMAT, __VA_ARGS__)
#define GE_LOG_CRITICAL(FORMAT, ...) GE_LOG_GENERIC(GE_Logger::LogMessageType::Critical, FORMAT, __VA_ARGS__)