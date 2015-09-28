# amon

Amon is a complex networks library I built with C++ to support my masters research. 

The library is intended to be simple and as fast as it can while being easy to read and understand. Some of the most taxing routines are implemented in parallel, using C++ 11 threads. 

The library itself is divided in 5 modules: graph, complex systems (csys), social, util and ai. This may grow in the future, but it works well for now. It is also well documented using Doxygen. 

The library is still growing, and just recently I started to support it as a C++ extension to Python. It is really lacking at exception handling, so if you're ever going to use it keep that in mind. :-)

To install:

If you're on linux, run premake5 gmake. That will generate some build files in the build/ directory. Go there and run sudo ./install.sh, that should take care of all. You should install boost aswell - that usually can be done using your package manager.

The build on MSV is broken because of threads. Sadly.
