#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "RTreeScene.h"

RTreeScene::RTreeScene(QObject* parent) :
    QGraphicsScene(parent)
{
    //setBackgroundBrush(QBrush("black"));
    addRect(0, 0, 1024, 512, QPen("black"), QBrush("black"));

}

void RTreeScene::setMode(const QString &mode)
{
    mMode = mode;
}

void RTreeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if ( mMode == "box" )
    {
        setSceneRect(0, 0, 1024, 1024);
        mSelectionRectItem = new QGraphicsRectItem();
        mSelectionRectItem->setPen(QColor("orange"));
        mFirstPoint = event->scenePos();
        addItem(mSelectionRectItem);
    }

    QGraphicsScene::mousePressEvent(event);
}

void RTreeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if ( mMode == "box" )
    {
        if ( !mSelectionRectItem )
            return;

        mSecondPoint = event->scenePos();
        mSelectionRect.setTopLeft(mFirstPoint);
        mSelectionRect.setBottomRight(mSecondPoint);

        mSelectionRectItem->setRect(mSelectionRect);
    }
    else
    {
        emit mouseMove(event->scenePos().x(), event->scenePos().y());
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void RTreeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if ( mMode == "box" )
    {
        if ( mSelectionRectItem )
        {
            delete mSelectionRectItem;
            mSelectionRectItem = nullptr;

            emit selectionAreaChanged(mSelectionRect);
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void RTreeScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}
