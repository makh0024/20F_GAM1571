workspace "Game"
	configurations { "Debug", "Release" }
	platforms 	   { "x64" }
	
	location 	   "build"
	
project "Game"
	kind "WindowedApp"
	
	files {
		"Game/Source/**.cpp",
		"Game/Source/**.h",
		"premake5.lua",
		"GenerateProjectFiles.bat",
		".gitignore",
	}
	
project "Framework"
	kind 		"StaticLib"
	location	"build/Framework"
	
	files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
	}
	