#include <QDebug>
#include <functional>

#include "RTreeContainer.h"

using namespace std::placeholders;

bool IsPoint(RTreeContainer::BoxValue const& v)
{
    qDebug() << __PRETTY_FUNCTION__;
    return std::get<2>(v) == 1;
}

bool IsRect(RTreeContainer::BoxValue const& v)
{
    qDebug() << __PRETTY_FUNCTION__;
    return std::get<2>(v) == 0;
}

RTreeContainer::RTreeContainer()
{
}

void RTreeContainer::addBox(double x, double y, double width, double height, unsigned int id)
{
    qDebug() << __PRETTY_FUNCTION__;
    bool isTriv = std::is_trivially_assignable<Box, Box>();
    qDebug() << "isTriv = " << isTriv;
    isTriv = std::is_trivially_assignable<unsigned int, unsigned int>();
    qDebug() << "isTriv = " << isTriv;
    isTriv = std::is_trivially_assignable<unsigned char, unsigned char>();
    qDebug() << "isTriv = " << isTriv;
    isTriv = std::is_trivially_assignable<BoxValue, BoxValue>();
    qDebug() << "isTriv = " << isTriv;


    RTreeContainer::Point p1(x, y);
    RTreeContainer::Point p2(x+width, y+height);

    RTreeContainer::Box b(p1, p2);

    mRTree.insert(std::make_tuple(b, id, 0));
}

void RTreeContainer::addPoint(double x, double y, unsigned int id)
{
    qDebug() << __PRETTY_FUNCTION__;
    bool isTriv = std::is_trivially_copyable<Point>();
    qDebug() << "isTriv = " << isTriv;
    isTriv = std::is_trivially_copyable<unsigned int>();
    qDebug() << "isTriv = " << isTriv;
    isTriv = std::is_trivially_copyable<unsigned char>();
    qDebug() << "isTriv = " << isTriv;
    isTriv = std::is_trivially_copyable<BoxValue>();

    RTreeContainer::Point p1(x-pointDiam, y-pointDiam);
    RTreeContainer::Point p2(x+pointDiam, y+pointDiam);

    RTreeContainer::Box pointBox(p1, p2);
    mRTree.insert(std::make_tuple(pointBox, id, 1));
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
                                                         //bgi::satisfies(IsRect));
          it != mRTree.qend(); ++it )
    {
        result.push_back(std::get<1>(*it));
    }

    return result;
}
