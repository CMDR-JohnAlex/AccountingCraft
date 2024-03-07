project "AccountingCraft"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c",
		"src/**.cpp",
		"src/**.hpp"
	}

	includedirs
	{
		"src",
		"vendor",
		"../ApplicationFramework/src",
		"../ApplicationFramework/vendor",
		"../ApplicationFramework/vendor/glfw/include",
		"../ApplicationFramework/vendor/glad/include",
		"../ApplicationFramework/vendor/ImGui",
		"../ApplicationFramework/vendor/ImGui/include",
		"../ApplicationFramework/vendor/ImGui/backends",
		"../ApplicationFramework/vendor/yaml-cpp/include",
		"../ApplicationFramework/vendor/stbi"
	}

	links
	{
		"ApplicationFramework"
	}

	filter "configurations:Debug"
		defines { "APPLICATION_FRAMEWORK_BUILD_DEBUG", "ACCOUNTING_CRAFT_BUILD_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "APPLICATION_FRAMEWORK_BUILD_RELEASE", "ACCOUNTING_CRAFT_BUILD_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines { "APPLICATION_FRAMEWORK_BUILD_DIST", "ACCOUNTING_CRAFT_BUILD_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"

	filter "system:windows"
		systemversion "latest"

		links
		{
		}

		defines
		{
			"APPLICATION_FRAMEWORK_PLATFORM_WINDOWS",
			"ACCOUNTING_CRAFT_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
		}

	filter "system:linux"

		links
		{
			"glad",
			"glfw",
			"ImGui",
			"imgui",
			"yaml-cpp",
			"GL",
			"X11",
			"Xi",
			"Xrandr",
			"Xxf86vm",
			"Xinerama",
			"Xcursor",
			"rt",
			"m",
			"pthread"
		}

		defines
		{
			"APPLICATION_FRAMEWORK_PLATFORM_LINUX",
			"ACCOUNTING_CRAFT_PLATFORM_LINUX"
		}

		postbuildcommands
		{
		}