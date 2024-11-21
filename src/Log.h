#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace ASM32 {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

}

#define TRACE(...)    ::ASM32::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define INFO(...)     ::ASM32::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WARN(...)     ::ASM32::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ERROR(...)    ::ASM32::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FATAL(...)    ::ASM32::Log::GetCoreLogger()->fatal(__VA_ARGS__)