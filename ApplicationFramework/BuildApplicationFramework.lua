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
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
		symbols "Off"