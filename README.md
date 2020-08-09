# BoostGeometryExperiment

Using Boost.Geometry library to better understand use of R-tree spatial index.

Uses Qt 5.15 and Boost 1.73, MinGW compiler on Windows.

Boost dependencies are included in the source tree.  Geometry is header only, no libraries are needed.

Program is a Qt app that lets you add random boxes and points (which are actually defined by Geometry boxes), and then select items using a rectangle or by moving mouse into proximity.

The geometry predicates nearest, within, and satisfies are used to find boxes in the R-tree.
