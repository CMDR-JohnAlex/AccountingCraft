workspace "AccountingCraft" -- Credit to Seagulldotexe
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "AccountingCraft"

	flags { "MultiProcessorCompile" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Program"
	include "AccountingCraft/BuildAccountingCraft.lua"
group ""

group "Dependencies"
	-- include ""
group ""