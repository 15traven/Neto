#include "logger.h"
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/msvc_sink.h>

std::shared_ptr<spdlog::logger> Logger::logger = spdlog::null_logger_mt("null");

bool Logger::was_log_failed_shown()
{
	wchar_t* p_value;
	size_t len;
	_wdupenv_s(&p_value, &len, log_failed_shown.c_str());
	delete[] p_value;
	return len;
}

void Logger::init(std::string loggerName)
{
	bool new_logger_created = false;
	try
	{
		logger = spdlog::get(loggerName);
		if (logger == nullptr)
		{
			auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
			logger = std::make_shared<spdlog::logger>(loggerName, sink);

			new_logger_created = true;
		}
	}
	catch (...)
	{
		logger = spdlog::null_logger_mt(loggerName);
		if (!was_log_failed_shown())
		{
			MessageBoxW(NULL, 
				L"Logger cannot be initialized", 
				L"Neto", 
				MB_OK | MB_ICONERROR);
		}

		return;
	}

	if (new_logger_created)
	{
		logger->set_level(spdlog::level::trace);
		logger->set_pattern("[%H:%M:%S] [%n] [%l] %v");
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
	}

	logger->info("{} logger is initialized", loggerName);
}