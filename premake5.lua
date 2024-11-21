workspace "ASM-32"
	architecture "x86_64"

	configurations {
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ASM-32"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"src",
		"libs/spdlog/include",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "ASM32_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ASM32_RELEASE"
		optimize "On"