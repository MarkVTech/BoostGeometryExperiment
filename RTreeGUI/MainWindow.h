#pragma once

#include <QMainWindow>
#include <QMap>

#include "RTreeContainer.h"

class RTreeScene;
class QRandomGenerator;
class ICommon;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static constexpr unsigned int minBoxSize = 10;
    static constexpr unsigned int maxBoxSize = 100;
    static constexpr unsigned int pointDiameter = 5;
    static constexpr unsigned int minXPos = 10;
    static constexpr unsigned int maxXPos = 600;
    static constexpr unsigned int minYPos = 10;
    static constexpr unsigned int maxYPos = 440;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleSelectionAreaChanged(const QRectF& selectionRect);
    void handleMouseMove(double x, double y);

    void on_actionAdd_Random_Point_triggered();
    void on_actionAdd_Random_Box_triggered();
    void on_actionSet_Box_Selection_Mode_triggered(bool flag);
    void on_actionSet_Nearest_Selection_Mode_triggered(bool flag);
    void on_actionClear_Selection_triggered();

private:
    Ui::MainWindow *ui;

    //QGraphicsScene* mScene;
    RTreeScene *mScene;
    QRandomGenerator* mRandomGenerator;

    QMap<unsigned int, ICommon*> mItemMap;
    unsigned int mItemID = 0;

    RTreeContainer mRTreeContainer;

    QString mMode = "box"; // or "near"

    std::vector<unsigned int> mCurrentlySelected;
    //std::vector<RTreeContainer::BoxValue> mCurrentlySelected;
};
