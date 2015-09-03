

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

	 platforms {
	 	"native",
        "win32",
        "win64",
        "macos",
        "linux86",
        "linux64",
    }

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

	configuration "vs2015"
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
	project "amon"
		kind "SharedLib"
		language  "C++"
		location  "build/"
		-- targetdir "lib/"
		-- targetdir "/usr/local/lib"
		files  {
			"src/graph/**.cpp",
			"src/csys/**.cpp",
			"src/social/**.cpp",
			"src/util/**.cpp",
		}
		links { "pthread" }

	project "amonet"
		kind "ConsoleApp"
		location  "build/"

		-- targetdir "bin/"
		-- targetdir "/usr/local/bin"
		-- targetdir "bin/"

		language  "C++"
		files  {
			"src/amon/**.cpp",
		}
		links { "pthread", "amon" } 

