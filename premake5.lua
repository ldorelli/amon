

-- premake5.lua
solution "AmonRa"
	configurations { "Debug", "Release" }
	location "build"

	filter "configurations:Debug"
		optimize "Debug"

	filter "configurations:Release"
		optimize "On"

	filter {}

	-- all include dirs
	includedirs { "includes/**" }

	-- configurations for GMAKE
	configuration "gmake"
		-- C++ 11
		buildoptions { "-std=c++11" }
		-- Needed on 64-bit platforms to be able
        -- to link static libraries to shared libraries.
        buildoptions { "-fPIC" }
        -- Enables some additional warnings.
        buildoptions { "-Wall" }

	-- -- independent, ai lib
	-- project "ai"
	-- 	kind "SharedLib"
	-- 	language  "C++"
	-- 	location  "build/ai"
	-- 	files  {
	-- 		"src/ai/src/**.cpp",
	-- 		"src/ai/header/**.hpp"
	-- 	}

	-- graph lib
	project "amon-graph"
		kind "SharedLib"
		language  "C++"
		location  "build/graph"
		targetdir "/usr/local/lib"
		files  {
			"src/graph/**.cpp",
		}

	-- -- complex systems lib 
	-- project "amon-csys"
	-- 	kind "SharedLib"
	-- 	language  "C++"
	-- 	location  "build/csys"
	-- 	files  {
	-- 		"src/csys/src/**.cpp",
	-- 	}

	-- -- social network stuff
	-- project "amon-social"
	-- 	kind "SharedLib"
	-- 	language  "C++"
	-- 	location  "build/soc"
	-- 	files  {
	-- 		"src/social/src/**.cpp",
	-- 	}

	-- utilities
	project "amon-utils"
		kind "StaticLib"
		language  "C++"
		location  "build/util"
		targetdir "/usr/local/lib"
		files  {
			"src/util/**.cpp",
		}

	project "amon"
		kind "ConsoleApp"
		location  "build/Amon"
		targetdir "/usr/local/bin"
		language  "C++"
		files  {
			"src/amon/**.cpp",
		}
		links { "amon-utils", "amon-graph" } 

