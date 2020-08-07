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

    //qDebug() << __PRETTY_FUNCTION__;

    if ( !((event->buttons() & Qt::LeftButton)  == Qt::LeftButton) && mMode == "nearest" )
        qDebug() << "YES!";

    if ( mMode == "box" )
    {
        if ( !mSelectionRectItem )
            return;

        mSecondPoint = event->scenePos();
        mSelectionRect.setTopLeft(mFirstPoint);
        mSelectionRect.setBottomRight(mSecondPoint);

        mSelectionRectItem->setRect(mSelectionRect);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void RTreeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if ( mMode == "box" )
    {
        if ( mSelectionRectItem )
        {
            qDebug() << "mSelectionRectItem = " << mSelectionRectItem << ", Selection area is " << mSelectionRect;
            delete mSelectionRectItem;
            mSelectionRectItem = nullptr;

            emit selectionChanged(mSelectionRect);
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void RTreeScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}


bool RTreeScene::event(QEvent *event)
{
    Q_UNUSED(event)
    //qDebug() << __PRETTY_FUNCTION__ << " type is " << event->type();
    if ( event->type() == QEvent::MouseMove )
        qDebug() << "HEY HEY HEY!";

    return QGraphicsScene::event(event);
}
