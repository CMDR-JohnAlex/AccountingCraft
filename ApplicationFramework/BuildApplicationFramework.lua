project "ApplicationFramework"
	kind "StaticLib"
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
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/ImGui",
		"vendor/ImGui/include",
		"vendor/ImGui/backends",
		"vendor/yaml-cpp/include",
		"vendor/stbi"
	}

	links
	{
		"glad",
		"glfw",
		"ImGui",
		"yaml-cpp"
	}

	filter "configurations:Debug"
		defines { "APPLICATION_FRAMEWORK_BUILD_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "APPLICATION_FRAMEWORK_BUILD_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "APPLICATION_FRAMEWORK_BUILD_DIST" }
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
			"APPLICATION_FRAMEWORK_PLATFORM_WINDOWS"
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
			"APPLICATION_FRAMEWORK_PLATFORM_LINUX"
		}

		postbuildcommands
		{
		}