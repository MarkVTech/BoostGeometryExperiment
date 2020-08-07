#pragma once

#include <QGraphicsEllipseItem>

#include "ICommon.h"

class QGraphicsItem;


class GraphicPoint : public QGraphicsEllipseItem, public ICommon
{
public:
    GraphicPoint(qreal x, qreal y, qreal width, qreal height, const QColor& color, const QColor &highlightColor, QGraphicsItem* parent=nullptr);

    // ICommon interface
public:
    void highlight(bool highlighted) override;

private:
    QColor mColor;
    QColor mHighlightColor;

};

