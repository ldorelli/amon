

-- premake5.lua
solution "Amonet"
	configurations { "Debug", "Release" }
	location "build"

	filter "configurations:Debug"
		optimize "Debug"

	filter "configurations:Release"
		optimize "On"

	filter {}

	-- all include dirs
	includedirs { "includes/", "/usr/include/python2.7/" }

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
 		-- GDB 
 		buildoptions { "-g" }
 		-- Optmize
 		buildoptions { "-O2" }
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
		files  {
			"src/graph/**.cpp",
			"src/csys/**.cpp",
			"src/social/**.cpp",
			"src/util/**.cpp",
		}
		links { "pthread", "boost_python-py27", "boost_system", "python2.7" }

	project "amonet"
		kind "ConsoleApp"
		location  "build/"
		language  "C++"
		files  {
			"src/amon/**.cpp",
		}
		links { "pthread",  "python2.7" , "amon" } 

