#include <QDebug>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QActionGroup>

#include <GraphicBox.h>
#include <GraphicPoint.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ICommon.h"
#include "RTreeScene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QActionGroup* group = new QActionGroup(this);
    QActionGroup* findWhatActionGroup = new QActionGroup(this);

    ui->setupUi(this);

    group->addAction(ui->actionSet_Box_Selection_Mode);
    group->addAction(ui->actionSet_Nearest_Selection_Mode);

    findWhatActionGroup->addAction(ui->actionFind_only_Boxes);
    findWhatActionGroup->addAction(ui->actionFind_only_Points);

    ui->actionSet_Box_Selection_Mode->setChecked(true);
    ui->actionFind_only_Boxes->setChecked(true);

    mScene = new RTreeScene(this);
    ui->graphicsView->setScene(mScene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    connect(mScene, SIGNAL(selectionChanged(QRectF)), this, SLOT(handleSelectionChanged(QRectF)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSelectionChanged(const QRectF &selectionRect)
{
    qDebug() << __PRETTY_FUNCTION__ << " selection: " << selectionRect;
    mCurrentlySelected = mRTree.within(
                selectionRect.x(), selectionRect.y(), selectionRect.width(), selectionRect.height(),
                ui->actionFind_only_Boxes->isChecked() ? 0 : 1);

    qDebug() << "Size of mCurrentlySelected = " << mCurrentlySelected.size();

    for ( auto index : mCurrentlySelected )
    {
        mItemMap[index]->highlight(true);
    }
}

void MainWindow::on_actionAdd_Random_Point_triggered()
{
    uint32_t x = QRandomGenerator::global()->bounded(maxXPos);
    uint32_t y = QRandomGenerator::global()->bounded(maxYPos);

    if ( x < minXPos-pointDiameter )
        x = 10;
    if ( y < minYPos-pointDiameter )
        y = 10;

    qDebug() << "x = " << x;

    QGraphicsItem* item = new GraphicPoint(x-pointDiameter, y-pointDiameter, pointDiameter, pointDiameter,
                                           QColor("yellow"), QColor("green"));
    mScene->addItem(item);

    mItemMap.insert(mItemID, dynamic_cast<ICommon*>(item));

    mRTree.addPoint(x, y,mItemID++);
}

void MainWindow::on_actionAdd_Random_Box_triggered()
{
    uint32_t x = QRandomGenerator::global()->bounded(maxXPos);
    uint32_t y = QRandomGenerator::global()->bounded(maxYPos);
    uint32_t w = QRandomGenerator::global()->bounded(maxBoxSize);
    uint32_t h = QRandomGenerator::global()->bounded(maxBoxSize);

    if ( x < minXPos )
        x = 10;
    if ( y < minYPos )
        y = 10;

    if ( w < minBoxSize )
        w = minBoxSize;
    if ( h < minBoxSize )
        h = minBoxSize;

    QGraphicsItem* item = new GraphicBox(x, y, w, h, QColor("red"), QColor("green"));
    mScene->addItem(item);

    mItemMap.insert(mItemID, dynamic_cast<ICommon*>(item));

    mRTree.addBox(x, y, w, h, mItemID++);
}

void MainWindow::on_actionSet_Box_Selection_Mode_triggered(bool flag)
{
    qDebug() << __PRETTY_FUNCTION__;

    if ( flag )
        mScene->setMode("box");
}

void MainWindow::on_actionSet_Nearest_Selection_Mode_triggered(bool flag)
{
    qDebug() << __PRETTY_FUNCTION__;

    if ( flag )
        mScene->setMode("nearest");
}

void MainWindow::on_actionClear_Selection_triggered()
{
    for ( auto index : mCurrentlySelected )
    {
        mItemMap[index]->highlight(false);
    }
    mCurrentlySelected.clear();
}
