#include "loading.h"
#include "ui_loading.h"
#include <QTimer>
#include <QDebug>
#include <qmath.h>


Loading::Loading(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Loading), _count(20), _idx(0), _minRadius(5), _maxRadius(30), _interval(50)
{
    ui->setupUi(this);

    for (int i = 0; i < _count; ++i)
    {
        Dot *dot = new Dot(this);
        dot->setColor(_color);
        dot->setRadius(_minRadius);

        _vecDots.push_back(dot);
    }

    calculate();
}

Loading::~Loading()
{
    delete ui;

    for (auto &dot : _vecDots)
    {
        dot->deleteLater();
        dot = nullptr;
    }
    _vecDots.clear();
}

void Loading::start()
{
    _t = new QTimer(this);
    connect(_t, &QTimer::timeout, this, &Loading::refresh);
    _t->setInterval(_interval);
    _t->start();
}

void Loading::stop()
{
    _t->stop();
    disconnect(_t, &QTimer::timeout, this, &Loading::refresh);
}

void Loading::setCount(int n)
{
    _count = n;
}

void Loading::setRadius(int min, int max)
{
    _minRadius = min;
    _maxRadius = max;
}

void Loading::setInterver(int interval)
{
    _interval = interval;
}

void Loading::setColor(const QColor &color)
{
    _color = color;
}

void Loading::calculate()
{
    QPoint center(width()/2, height()/2);
    double interAngle = 360.0 / _count;
    int len = static_cast<int>(fmin(width(), height()) - 100) / 2;
    double interRadius = (_maxRadius - _minRadius) / _count;

    for (int i = 0; i < _count; ++i)
    {
        double angle = interAngle * i;
        int x = static_cast<int>(len*cos(qDegreesToRadians(angle)) + center.x());
        int y = static_cast<int>(len*sin(qDegreesToRadians(angle)) + center.y());

        if (_idx > i ) _vecDots.at(i)->setRadius(static_cast<int>(_maxRadius - (_idx - i) * interRadius));
        else _vecDots.at(i)->setRadius(static_cast<int>(_maxRadius - (_idx + _count - i) * interRadius));

        _vecDots.at(i)->setPos(x, y);
        _vecDots.at(i)->setColor(QColor(188, 10*i, 255-10*i));
    }

    _idx = (_idx + 1) % _count;
}

void Loading::refresh()
{
    calculate();
    repaint();
}



