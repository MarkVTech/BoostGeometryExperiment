#pragma once

#include <memory>
#include <vector>
#include <tuple>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/index/rtree.hpp>

#include <QDebug>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;


struct Info
{
    unsigned int id;
    unsigned char type;
};

class RTreeContainer
{
public:
    static const int pointDiam=10;

    typedef bg::model::point<unsigned int, 2, bg::cs::cartesian> Point;
    typedef bg::model::box<Point> Box;
    //typedef std::tuple<Box, unsigned int, unsigned char> BoxValue;
    typedef std::pair<Box, Info> BoxValue;
    typedef bgi::rtree<BoxValue, bgi::rstar<16,4>> RTree;

    RTreeContainer();

    void addBox(double x, double y, double width, double height, unsigned int id);
    void addPoint(double x, double y, unsigned int id);

    std::vector<unsigned int> within(double x, double y, double width, double height, unsigned int itemType);
    std::vector<unsigned int> nearest(double x, double y, unsigned int itemType);

private:
    RTree mRTree;
};
