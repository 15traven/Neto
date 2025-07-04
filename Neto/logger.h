#pragma once

#include <spdlog/spdlog.h>

class Logger
{
private:
	static std::shared_ptr<spdlog::logger> logger;
	inline const static std::wstring log_failed_shown = L"log_failed_shown";
	static bool was_log_failed_shown();
public:
	Logger() = delete;

	static void init(std::string loggerName);

	template<typename FormatString, typename... Args>
	static void trace(const FormatString& fmt, const Args&... args)
	{
		logger->trace(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void debug(const FormatString& fmt, const Args&... args)
	{
		logger->debug(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void info(const FormatString& fmt, const Args&... args)
	{
		logger->info(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void warn(const FormatString& fmt, const Args&... args)
	{
		logger->warn(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void error(const FormatString& fmt, const Args&... args)
	{
		logger->error(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void critical(const FormatString& fmt, const Args&... args)
	{
		logger->critical(fmt, args...);
	}

	static void flush()
	{
		logger->flush();
	}
};