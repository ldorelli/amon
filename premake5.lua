-- premake5.lua
solution "Amonet"
	configurations { "Debug", "Release" }
	
	configuration {}
	location "build"

	filter "configurations:Debug"
		optimize "Debug"

	filter "configurations:Release"
		optimize "On"

	filter {}

	-- all include dirs
	includedirs { "includes/" , "includes/python2.7/" }

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
		buildoptions { "-std=c++0x" }
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

	-- graph lib
	project "amon"
		kind "SharedLib"
		language  "C++"
		location  "build/"
		targetdir "build/"
		files  {
			"src/amon_python.cpp",
			"src/graph/**.cpp",
			"src/csys/**.cpp",
			"src/social/**.cpp",
			"src/util/**.cpp",
		}
		links { "pthread", "boost_python-py27", "boost_system", "python2.7", "gmp", "gmpxx" }
