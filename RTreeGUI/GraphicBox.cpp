#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QColor>

#include "GraphicBox.h"

GraphicBox::GraphicBox(qreal x, qreal y, qreal width, qreal height, const QColor &color, const QColor &hightlightColor, QGraphicsItem* parent) :
    QGraphicsRectItem(x, y, width, height, parent),
    mColor(color),
    mHighlightColor(hightlightColor)
{
    setPen(color);
}


void GraphicBox::highlight(bool highlighted)
{
    if ( mIsHighlighted == highlighted )
        return;

    if ( highlighted )
        setPen(mHighlightColor);
    else
        setPen(mColor);

    mIsHighlighted = highlighted;
}

void newFunctionForSwimm()
{
}
