#include "showwindow.h"
#include "loading.h"
#include "lednumber.h"
#include "roundprogressbar.h"
#include "waterprogressbar.h"
#include "battery.h"
#include "speedpanel.h"
#include "shipscale.h"
#include "ship.h"
#include "HUD/HUDGraph.h"
#include "NumberAnimation/numberanimation.h"
#include <QTableWidget>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QSplitter>
#include <QGraphicsView>


ShowWindow::ShowWindow(QWidget *parent)
    : QWidget(parent)
{
    init();
}

void ShowWindow::init()
{
    resize(800, 600);
    QHBoxLayout *hl = new QHBoxLayout(this);
    _tabWgt = new QTabWidget(this);
    hl->addWidget(_tabWgt);

    initLoading();
    initLEDNumber();
    initProgress();
    initWaterProgress();
    initBattery();
    initSpeedPanel();
    initShip();
    initHUD();
    initNumberAnimation();
}

void ShowWindow::initLoading()
{
    _wgtLoading = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtLoading, "Loading");
    QHBoxLayout *hl = new QHBoxLayout(_wgtLoading);

    Loading *load = new Loading(_wgtLoading);
    hl->addWidget(load);
    load->start();
}

void ShowWindow::initLEDNumber()
{
    _wgtLEDNumber = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtLEDNumber, "LEDNumber");
    QHBoxLayout *hl = new QHBoxLayout(_wgtLEDNumber);

    for (int i = 0; i < 3; ++i)
    {
        LEDNumber *num = new LEDNumber(_wgtLEDNumber);
        num->setColor(QColor(i*80, 255-i*80, 188), QColor(188, i*80, 255-80*i));
        hl->addWidget(num);
        num->start();
    }
}

void ShowWindow::initProgress()
{
    _wgtProgress = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtProgress, "RoundProgressBar");
    QHBoxLayout *hl = new QHBoxLayout(_wgtProgress);

    for (int i = 0; i < 2; ++i)
    {
        RoundProgressBar *progress = new RoundProgressBar(_wgtProgress);
        hl->addWidget(progress);
        progress->start();
    }
}

void ShowWindow::initWaterProgress()
{
    _wgtWaterProgress = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtWaterProgress, "WaterProgressBar");
    QHBoxLayout *hl = new QHBoxLayout(_wgtWaterProgress);

    for (int i = 0; i < 2; ++i)
    {
        WaterProgressBar *progress = new WaterProgressBar(_wgtWaterProgress);
        hl->addWidget(progress);
        progress->start();
    }
}

void ShowWindow::initBattery()
{
    _wgtBattery = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtBattery, "Battery");
    QHBoxLayout *hl = new QHBoxLayout(_wgtBattery);

    for (int i = 0; i < 3; ++i)
    {
        Battery *num = new Battery(_wgtBattery);
        num->setColor(QColor(i*80, 255-i*80, 188));
        hl->addWidget(num);
        num->start();
    }
}

void ShowWindow::initSpeedPanel()
{
    _wgtSpeedPanel = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtSpeedPanel, "SpeedPanel");
    QHBoxLayout *hl = new QHBoxLayout(_wgtSpeedPanel);

    for (int i = 0; i < 2; ++i)
    {
        SpeedPanel *speed = new SpeedPanel(_wgtSpeedPanel);
        speed->setColor(QColor(i*80, 255-i*80, 100), QColor(100, i*80, 255-i*80));
        hl->addWidget(speed);
        speed->start();
    }
}

void ShowWindow::initShip()
{
    _wgtShip = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtShip, "Ship");
    QHBoxLayout *hl = new QHBoxLayout(_wgtShip);

//    for (int i = 0; i < 2; ++i)
//    {
//        ShipScale *ship = new ShipScale(_wgtShip);
//        ship->setColor(QColor(i*80, 255-i*80, 222), QColor(255-i*80, 222, i*80));
//        hl->addWidget(ship);
//        ship->start();
//    }

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ShipScale *scale = new ShipScale();
    scene->addWidget(scale);
    int count = 6;

    for (int i = 0; i < count; ++i) {
        Ship *ship = new Ship;
        ship->setPos(::sin((i * 6.28) / count) * 200,
                      ::cos((i * 6.28) / count) * 200);
        ship->setPos(200, 200);
        scene->addItem(ship);
    }

    QGraphicsView *view = new QGraphicsView(_wgtShip);
    hl->addWidget(view);
    view->setAlignment(Qt::AlignCenter);
    view->setScene(scene);
//    view->setRenderHint(QPainter::Antialiasing);
//    view->setBackgroundBrush(Qt::white);
//    view->setCacheMode(QGraphicsView::CacheBackground);
//    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    view->setDragMode(QGraphicsView::ScrollHandDrag);
//    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Ship"));

    QTimer *timer = new QTimer(this);
    QObject::connect (timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);
}

void ShowWindow::initHUD()
{
    _wgtHUD = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtHUD, "HUD Graph");
    QHBoxLayout *hl = new QHBoxLayout(_wgtHUD);

    for (int i = 0; i < 2; ++i)
    {
        HUDGraph *hud = new HUDGraph(_wgtHUD);
        hud->setColor(QColor(66, 255-66*i, 66*i), QColor(66*i, 188-66*i, 188));
        hud->start();
        hl->addWidget(hud);
    }
}

void ShowWindow::initNumberAnimation()
{
    _wgtNumberAnimation = new QWidget(_tabWgt);
    _tabWgt->addTab(_wgtNumberAnimation, "Number Animation");
    QHBoxLayout *hl = new QHBoxLayout(_wgtNumberAnimation);

    for (int i = 0; i < 2; ++i)
    {
        static bool flag = true;
        NumberAnimation *na = new NumberAnimation(_wgtNumberAnimation);
        na->setLoop(true);
        na->setClockwise(flag);
        na->start();
        hl->addWidget(na);

        flag = !flag;
    }
}




