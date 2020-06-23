#include "shipscale.h"
#include <QTimer>
#include <QPainter>
#include <QPolygon>


ShipScale::ShipScale(QWidget *parent)
    : QWidget(parent), _value(75), _bgColor(Qt::gray), _lineColor(Qt::blue)
{
    init();
}

void ShipScale::start()
{
    connect(_t, &QTimer::timeout, this, &ShipScale::refresh);
    _t->setInterval(1000);
    _t->start();
}

void ShipScale::setValue(int v)
{
    _ani->setStartValue(_value);
    _ani->setEndValue(v);
    _ani->start();

    if (v <= -180) _value = 0;
    else if (v > 180) _value = 180;
    else _value = v;
}

void ShipScale::setColor(const QColor &bgColor, const QColor &lineColor)
{
    _bgColor = bgColor;
    _lineColor = lineColor;
}

void ShipScale::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    drawScale(p);
    drawCircle(p);
    drawPointer(p);

    QWidget::paintEvent(event);
}

void ShipScale::init()
{
    _t = new QTimer(this);
    _ani = new QPropertyAnimation(this, "_value");
    _ani->setDuration(500);
    _ani->setEasingCurve(QEasingCurve::OutQuad);
}

void ShipScale::drawCircle(QPainter &p)
{
    int len = (width() < height() ? width() : height()) - 50;

    p.save();

    p.translate(width()/2, height()/2);

    // Draw outter circle
    QPen pen(_lineColor);
    pen.setWidth(5);
    p.setPen(pen);
    QRect rect(-len/2, -len/2, len, len);
    p.drawEllipse(rect);

    // Draw middle circle
    p.scale(0.5, 0.5);
    pen.setWidth(10);
    p.setPen(pen);
    p.drawEllipse(rect);

    // Draw inner circle
    p.scale(0.2, 0.2);
    pen.setWidth(60);
    p.setPen(pen);
    p.drawEllipse(rect);

    p.restore();
}

void ShipScale::drawScale(QPainter &p)
{
    int len = (width() < height() ? width() : height()) - 50;
    int count = 12;
    int angle = 360 / count;

    p.save();

    p.translate(width()/2, height()/2);

    // Draw long scales
    QPen pen;
    for (int i = 0; i < count; ++i)
    {
        pen.setWidth(3);
        p.setPen(pen);
        p.drawLine(len/2, 0, len/2-20, 0);
        p.rotate(angle);
    }

    // Draw short scales
    p.rotate(angle/2);
    for (int i = 0; i < count; ++i)
    {
        pen.setWidth(2);
        p.setPen(pen);
        p.drawLine(len/2, 0, len/2-10, 0);
        p.rotate(angle);
    }

    // Draw 2 lines
    p.rotate(-angle/2);
    pen.setColor(Qt::gray);
    p.setPen(pen);
    p.drawLine(-len/2, 0, len/2, 0);

    p.rotate(90);
    p.drawLine(-len/2, 0, len/2, 0);

    p.restore();
}

void ShipScale::drawPointer(QPainter &p)
{
    int len = (width() < height() ? width() : height()) - 50;

    p.save();

    p.translate(width()/2, height()/2);
    p.rotate(-_value);

    // Draw pointer
    QLinearGradient lg;
    lg.setColorAt(0.0, Qt::white);
    lg.setColorAt(0.5, Qt::blue);
    lg.setColorAt(1.0, Qt::green);
    QBrush brush(lg);
    p.setBrush(brush);

    QVector<QPoint> points = { QPoint(0, -3), QPoint(0, 3), QPoint(len/2-30, 0) };
    QPainterPath path;
    path.addPolygon(QPolygon(points));
    p.fillPath(path, lg);

    p.restore();
}

void ShipScale::_setValue(int v)
{
    _value = v;
    update();
}

void ShipScale::refresh()
{
    setValue(qrand() % 360 - 180);
    update();
}


