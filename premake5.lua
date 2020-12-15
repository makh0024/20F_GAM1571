workspace "Game"
	configurations { "Debug", "Release" }
	platforms 	   { "x64" }
	
	location 	   "build"
	characterset   "MBCS"
	startproject   "GameCustom"
	
	filter "configurations:Debug"
	symbols "on"
	
-- project "Game"
	-- kind	 "WindowedApp"
	-- location "build/Game"
	-- debugdir "Game"
	
	-- files {
		-- "Game/Source/**.cpp",
		-- "Game/Source/**.h",
		-- "Game/Data/**.vert",
		-- "Game/Data/**.frag",
		-- "premake5.lua",
		-- "ReadMe.txt"
		-- "GenerateProjectFiles.bat",
		-- ".gitignore",
	-- }
	
	-- includedirs {
		-- "Framework/Source",
		-- "Game/Source",
	-- }
	
	-- links {
		-- "Framework",
		-- "opengl32",
	-- }
	
	-- pchheader "GamePCH.h"
	-- pchsource "Game/Source/WinMain.cpp"
	
project "GameCustom"
	kind	 "WindowedApp"
	location "build/GameCustom"
	debugdir "GameCustom"
	
	files {
		"GameCustom/Source/**.cpp",
		"GameCustom/Source/**.h",
		"GameCustom/Data/**.vert",
		"GameCustom/Data/**.frag",
		"GameCustom/Data/**.json",
		"premake5.lua",
		"GenerateProjectFiles.bat",
		".gitignore",
	}
	
	includedirs {
		"GameCustom/Source",
	}
	
	links {
		"Framework",
		"opengl32",
	}
	
	pchheader "GamePCH.h"
	pchsource "GameCustom/Source/WinMain.cpp"
	
project "Framework"
	kind 		"StaticLib"
	location	"build/Framework"
	
	files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
		"Framework/Libraries/**.cpp",
		"Framework/Libraries/**.h",
	}
	
	includedirs {
		"Framework/Source",
	}
	
	filter "files:Framework/Libraries/imgui/*.cpp"
		flags { 'NoPCH' }
	
	pchheader "FrameworkPCH.h"
	pchsource "Framework/Source/Core/FWCore.cpp"
	
	