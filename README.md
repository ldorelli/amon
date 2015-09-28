# amon

Amon is a complex networks library I built with C++ to support my masters research. 

The library is intended to be simple and as fast as it can while being easy to read and understand. Some of the most taxing routines are implemented in parallel, using C++ 11 threads. 

The library itself is divided in 5 modules: graph, complex systems (csys), social, util and ai. This may grow in the future, but it works well for now. It is also well documented using Doxygen. 

The library is still growing, and just recently I started to support it as a C++ extension to Python. It is really lacking at exception handling, so if you're ever going to use it keep that in mind. :-)
