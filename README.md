# BoostGeometryExperiment

Using Boost.Geometry library to better understand use of R-tree spatial index.

Uses Qt 5.15 and Boost 1.73, MinGW compiler on Windows.

Note BOOST_PATH environment variable in .pro.  You will need to build Boost with the correct compiler (i.e., MinGW in my case).

Program is a Qt app that lets you add random boxes and points (which are actually defined by Geometry boxes), and then select items using a rectangle.
