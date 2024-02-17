workspace "AccountingCraft" -- Credit to Seagulldotexe for the name
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "AccountingCraft"

	-- Workspace-wide build options for MSVC
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

	flags { "MultiProcessorCompile" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Program"
	include "AccountingCraft/BuildAccountingCraft.lua"
group ""

group "Framework"
	include "ApplicationFramework/BuildApplicationFramework.lua"
group ""

group "Dependencies"
	include "ApplicationFramework/vendor/glfw/premake5.lua"
	include "ApplicationFramework/vendor/glad/premake5.lua"
	include "ApplicationFramework/vendor/ImGui/premake5.lua"
	include "ApplicationFramework/vendor/yaml-cpp/premake5.lua"
group ""