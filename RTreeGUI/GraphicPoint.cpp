#include <QDebug>
#include "GraphicPoint.h"

#include <QPen>

GraphicPoint::GraphicPoint(qreal x, qreal y, qreal width, qreal height, const QColor &color, const QColor &highlightColor, QGraphicsItem *parent) :
    QGraphicsEllipseItem(x, y, width, height, parent),
    mColor(color),
    mHighlightColor(highlightColor)
{
    setPen(color);
    setBrush(color);
}


void GraphicPoint::highlight(bool highlighted)
{
    if ( mIsHighlighted == highlighted )
        return;

    if ( highlighted )
    {
        setPen(mHighlightColor);
        setBrush(mHighlightColor);
    }
    else
    {
        setPen(mColor);
        setBrush(mColor);
    }

    mIsHighlighted = highlighted;
}
