

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
       -- Because yes
        buildoptions { "-Wl,--no-as-needed" }
		-- C++ 11
		buildoptions { "-std=c++1y" }
		-- Needed on 64-bit platforms to be able
        -- to link static libraries to shared libraries.
        buildoptions { "-fPIC" }
        -- Enables some additional warnings.
        buildoptions { "-Wall" }
 		-- GDB 
 		buildoptions { "-g" }

        -- Oh well
        buildoptions { "-pthread" }

        -- Link pthread
		linkoptions { "-pthread" }        
		-- gdb
		linkoptions { "-g" }        


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
		links { "pthread" }

	-- complex systems lib 
	project "amon-csys"
		kind "SharedLib"
		language  "C++"
		location  "build/csys"
		targetdir "/usr/local/lib"
		files  {
			"src/csys/**.cpp",
		}
		links { "amon-graph", "pthread" }

	-- social network stuff
	project "amon-social"
		kind "SharedLib"
		language  "C++"
		location  "build/soc"
		targetdir "/usr/local/lib"
		files  {
			"src/social/**.cpp",
		}
		links { "amon-graph","amon-utils", "pthread" }

	-- utilities
	project "amon-utils"
		kind "SharedLib"
		language  "C++"
		location  "build/util"
		targetdir "/usr/local/lib"
		files  {
			"src/util/**.cpp",
		}
		links { "pthread" }

	project "amon"
		kind "ConsoleApp"
		location  "build/Amon"
		targetdir "/usr/local/bin"
		language  "C++"
		files  {
			"src/amon/**.cpp",
		}
		links { "pthread", "amon-utils", "amon-graph", "amon-csys", "amon-social" } 

