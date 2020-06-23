#include "battery.h"
#include <QPainter>
#include <QPainterPath>


Battery::Battery(QWidget *parent)
    : QWidget(parent), _value(30)
{
    init();
}

void Battery::start()
{
    connect(_t, &QTimer::timeout, this, &Battery::refresh);
    _t->setInterval(1000);
    _t->start();
}

void Battery::setValue(int v)
{
    _ani->setStartValue(_value);
    _ani->setEndValue(v);
    _ani->start();

    _value = v;
}

void Battery::setColor(const QColor &bgColor)
{
    _bgColor = bgColor;
}

void Battery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    drawBorder(&p);
    drawCapacity(&p);
    drawText(&p);
}

void Battery::init()
{
    _t = new QTimer(this);
    _ani = new QPropertyAnimation(this, "_value");
    _ani->setDuration(500);
    _ani->setEasingCurve(QEasingCurve::OutQuad);
}

void Battery::drawBorder(QPainter *p)
{
    p->save();

    int w1 = static_cast<int>(width()*0.2);
    int h1 = static_cast<int>(height()*0.8);

    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(3);
    p->setPen(pen);
    p->drawRect(5, 5, width()-10, h1);
    p->drawRect(w1, h1+6, static_cast<int>(width()*0.6-10), static_cast<int>(height()*0.1-10));

    p->restore();
}

void Battery::drawCapacity(QPainter *p)
{
    p->save();

    int h = static_cast<int>(height()*0.8 * _value / 100);

    QBrush brush(_bgColor);
    p->setBrush(brush);
    p->drawRect(5, 5, width()-10, h);

    p->restore();
}

void Battery::drawText(QPainter *p)
{
    p->save();

    int w1 = static_cast<int>(width()*0.2);
    int h1 = static_cast<int>(height()*0.8);

    QPen pen;
    pen.setColor(Qt::blue);
    p->setPen(pen);
    QFont font("楷体", 24, 5);
    p->setFont(font);
    p->drawText(QRect(w1, h1+6, static_cast<int>(width()*0.6-10), static_cast<int>(height()*0.1-10)), Qt::AlignCenter, QString::number(_value).append("%"));

    p->restore();
}

void Battery::_setValue(int v)
{
    _value = v;
    repaint();
}

void Battery::refresh()
{
    setValue(qrand() % 100);
    repaint();
}


