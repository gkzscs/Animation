#include "dot.h"
#include <QPainter>


Dot::Dot(QWidget *parent) :
    QWidget(parent), _bgColor(Qt::green), _radius(30)
{
    resize(60, 60);
}

void Dot::setColor(const QColor &color)
{
    _bgColor = color;
}

void Dot::setRadius(int r)
{
    _radius = r;
}

void Dot::setPos(int x, int y)
{
    move(x-_radius, y-_radius);
}

void Dot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(_bgColor);
    p.drawEllipse(QPoint(_radius, _radius), _radius, _radius);
}
