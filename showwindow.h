#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QWidget>

class QTabWidget;


class ShowWindow : public QWidget
{
    Q_OBJECT

public:
    ShowWindow(QWidget *parent = nullptr);

private:
    void init();
    void initLoading();
    void initLEDNumber();
    void initProgress();
    void initWaterProgress();
    void initBattery();
    void initSpeedPanel();
    void initShip();
    void initHUD();
    void initNumberAnimation();

private:
    QTabWidget *_tabWgt;
    QWidget *_wgtLoading;
    QWidget *_wgtLEDNumber;
    QWidget *_wgtProgress;
    QWidget *_wgtWaterProgress;
    QWidget *_wgtBattery;
    QWidget *_wgtSpeedPanel;
    QWidget *_wgtShip;
    QWidget *_wgtHUD;
    QWidget *_wgtNumberAnimation;

};

#endif // SHOWWINDOW_H
