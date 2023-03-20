#include <QDebug>
#include <functional>

#include "RTreeContainer.h"

using namespace std::placeholders;

bool IsPoint(RTreeContainer::BoxValue const& v)
{
    // A comment
    return v.second.type == 1;
}

bool IsRect(RTreeContainer::BoxValue const& v)
{
    return v.second.type == 0;
}

bool IsWithinRange(RTreeContainer::BoxValue const& v, double x, double y, double distance)
{
    return bg::distance(v.first, RTreeContainer::Point(x, y)) < distance;
}

RTreeContainer::RTreeContainer()
{
}

void RTreeContainer::addBox(double x, double y, double width, double height, unsigned int id)
{
    RTreeContainer::Point p1(x, y);
    RTreeContainer::Point p2(x+width, y+height);

    RTreeContainer::Box b(p1, p2);

    mRTree.insert(std::make_pair(b, Info{id, 0}));
}

void RTreeContainer::addPoint(double x, double y, unsigned int id)
{
    RTreeContainer::Point p1(x-pointDiam, y-pointDiam);
    RTreeContainer::Point p2(x+pointDiam, y+pointDiam);

    RTreeContainer::Box pointBox(p1, p2);
    mRTree.insert(std::make_pair(pointBox, Info{id, 1}));
}

std::vector<unsigned int> RTreeContainer::within(double x, double y, double width, double height, unsigned int itemType)
{
    std::vector<unsigned int> result;

    RTreeContainer::Point p1(x, y);
    RTreeContainer::Point p2(x+width, y+height);
    RTreeContainer::Box box_region(p1, p2);

    std::function<bool(RTreeContainer::BoxValue const&)> func;

    if ( itemType == 0 )
        func = std::bind(&IsRect, _1);
    else
        func = std::bind(&IsPoint, _1);

    for ( RTree::const_query_iterator it = mRTree.qbegin(bgi::within(box_region) &&
                                                         bgi::satisfies(func));
          it != mRTree.qend(); ++it )
    {
        result.push_back(it->second.id);
    }

    return result;
}

std::vector<unsigned int> RTreeContainer::nearest(double x, double y, unsigned int itemType)
{
    std::vector<unsigned int> result;

    RTreeContainer::Point p(x, y);

    std::function<bool(RTreeContainer::BoxValue const&)> typeFunc;

    if ( itemType == 0 )
        typeFunc = std::bind(&IsRect, _1);
    else
        typeFunc = std::bind(&IsPoint, _1);

    auto rangeFunc = std::bind(&IsWithinRange, _1, x, y, 5);
    for ( RTree::const_query_iterator it = mRTree.qbegin(bgi::satisfies(rangeFunc) &&
                                                         bgi::satisfies(typeFunc));
          it != mRTree.qend(); ++it )
    {
        result.push_back(it->second.id);
    }

    return result;
}
