#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace ASM32 {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^%l: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("ASM32");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
	
}