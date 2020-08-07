#pragma once

#include <QGraphicsScene>

class QGraphicsRectItem;

class RTreeScene : public QGraphicsScene
{
    Q_OBJECT

public:
    RTreeScene(QObject* parent=nullptr);

    void setMode(const QString& mode);

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void selectionChanged(const QRectF& selectionRect);

private:
    QGraphicsRectItem *mSelectionRectItem = nullptr;
    QPointF mFirstPoint;
    QPointF mSecondPoint;
    QRectF mSelectionRect;

    QString mMode = "box";

    // QObject interface
public:
    bool event(QEvent *event) override;
};

