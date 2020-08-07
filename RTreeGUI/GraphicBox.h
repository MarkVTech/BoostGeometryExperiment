#pragma once

#include "ICommon.h"

#include <QGraphicsRectItem>
#include <QColor>

class QGraphicsItem;

class GraphicBox : public QGraphicsRectItem, public ICommon
{
public:
    GraphicBox(qreal x, qreal y, qreal width, qreal height,
               const QColor& color, const QColor& hightlightColor, QGraphicsItem* parent=nullptr);

    // ICommon interface
public:
    void highlight(bool highlighted) override;

private:
    QColor mColor;
    QColor mHighlightColor;
};

