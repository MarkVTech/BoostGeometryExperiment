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
    void selectionAreaChanged(const QRectF& selectionRect);
    void mouseMove(double x, double y);

private:
    QGraphicsRectItem *mSelectionRectItem = nullptr;
    QPointF mFirstPoint;
    QPointF mSecondPoint;
    QRectF mSelectionRect;

    QString mMode = "box";

};

