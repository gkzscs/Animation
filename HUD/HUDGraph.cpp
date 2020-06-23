#include "HUDGraph.h"
#include <QPainter>


HUDGraph::HUDGraph(QWidget *parent)
    : QWidget(parent), _pitch(0), _roll(30), _skyColor(Qt::blue), _groundColor(Qt::yellow)
{
    init();
}

void HUDGraph::start()
{
    connect(_t, &QTimer::timeout, this, &HUDGraph::refresh);
    _t->setInterval(1000);
    _t->start();
}

void HUDGraph::setPitch(double pitch)
{
    _aniPitch->setStartValue(_pitch);
    _aniPitch->setEndValue(pitch);
    _aniPitch->start();

    if (pitch < -90) _pitch = -90;
    else if (pitch > 90) _pitch = 90;
    else _pitch = pitch;

    update();
}

void HUDGraph::setRoll(double roll)
{
    _aniRoll->setStartValue(_roll);
    _aniRoll->setEndValue(roll);
    _aniRoll->start();

    if (roll < -180) _roll = -180;
    else if (roll > 180) _roll = 180;
    else _roll = roll;

    update();
}

void HUDGraph::setColor(const QColor &skyColor, const QColor &groundColor)
{
    _skyColor = skyColor;
    _groundColor = groundColor;

    update();
}

void HUDGraph::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    drawBackground(p);
    drawPitch(p);
    drawRoll(p);
}

void HUDGraph::keyPressEvent(QKeyEvent *event)
{

}

void HUDGraph::init()
{
    _t = new QTimer(this);
    _aniPitch = new QPropertyAnimation(this, "_pitch");
    _aniRoll = new QPropertyAnimation(this, "_roll");
    _aniPitch->setDuration(500);
    _aniPitch->setEasingCurve(QEasingCurve::OutQuad);
    _aniRoll->setDuration(500);
    _aniRoll->setEasingCurve(QEasingCurve::OutQuad);
}

void HUDGraph::drawBackground(QPainter &p)
{
    int len = (width() < height() ? width() : height()) - 50;

    p.save();
    p.translate(width()/2, height()/2);
    p.rotate(_roll);

    // Draw sky
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_skyColor);
    p.setBrush(brush);
    p.drawChord(-len/2, -len/2, len, len, 0, 180*16);

    // Draw ground
    brush.setColor(_groundColor);
    p.setBrush(brush);
    p.drawChord(-len/2, -len/2, len, len, 180*16, 180*16);

    p.restore();
}

void HUDGraph::drawPitch(QPainter &p)
{
    int len = (width() < height() ? width() : height()) - 50;

    p.save();
    p.translate(width()/2, height()/2);
    p.rotate(_roll);

    // Draw scale
    const int count = 6;
    const int l = len / 4;

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    p.setPen(pen);

    for (int i = 0; i < count; ++i)
    {
        int ll = l / 2;
        if (i%3 == 0) ll = l;
        p.drawLine(-ll/2, 0, ll/2, 0);
        if (i%3 == 0 && i != 0)
        {
            p.setFont(QFont("楷体", 12, 1));
            p.drawText(QRect(-ll/2-30, -10, 25, 20), Qt::AlignRight, QString::number(-i*10));
        }
        p.translate(0, len/count/2);
    }
    p.translate(0, -len/2);
    for (int i = 0; i < count; ++i)
    {
        int ll = l / 2;
        if (i%3 == 0) ll = l;
        p.drawLine(-ll/2, 0, ll/2, 0);
        if (i%3 == 0 && i != 0)
        {
            p.setFont(QFont("楷体", 12, 1));
            p.drawText(QRect(-ll/2-30, -10, 25, 20), Qt::AlignRight, QString::number(i*10));
        }
        p.translate(0, -len/count/2);
    }
    p.translate(0, len/2);

    // Draw center scale
    pen.setColor(Qt::darkRed);
    p.setPen(pen);
    p.drawLine(-l, 0, l, 0);
    p.setFont(QFont("楷体", 12, 1));
    p.drawText(QRect(-l-30, -10, 25, 20), Qt::AlignRight, QString::number(0));

    // Draw pointer
    p.translate(-l/4, 0);
    QBrush brush(Qt::red);
    p.setBrush(brush);
    QPoint points[] = { QPoint(-10, -5), QPoint(-10, 5), QPoint(0, 0) };
    p.drawPolygon(points, 3);

    p.translate(l/2, 0);
    QPoint points2[] = { QPoint(10, -5), QPoint(10, 5), QPoint(0, 0) };
    p.drawPolygon(points2, 3);

    p.restore();
}

void HUDGraph::drawRoll(QPainter &p)
{
    int len = (width() < height() ? width() : height()) - 50;

    p.save();
    p.translate(width()/2, height()/2);
    p.rotate(_roll);

    // Draw scale
    int count = 12;
    int interAngle = 360 / count;
    int l = 10;
    for (int i = 0; i < count; ++i)
    {
        int num = (i*30 <= 180 ? i*30 : i*30-360);
        p.drawText(QRect(len/2-l-25, -10, 25, 20), Qt::AlignCenter, QString::number(num));
        p.drawLine(len/2-l, 0, len/2, 0);
        p.rotate(-interAngle/3);
        p.drawLine(len/2-l/2, 0, len/2, 0);
        p.rotate(-interAngle/3);
        p.drawLine(len/2-l/2, 0, len/2, 0);
        p.rotate(-interAngle/3);
    }

    // Draw pointer
    p.translate(0, 45-len/2);
    QBrush brush(Qt::yellow);
    p.setBrush(brush);

    QPoint points[] = { QPoint(-5, 0), QPoint(5, 0), QPoint(0, -10) };
    p.drawPolygon(points, 3);

    p.restore();
}

void HUDGraph::_setPitch(double pitch)
{
    if (pitch < -90) _pitch = -90;
    else if (pitch > 90) _pitch = 90;
    else _pitch = pitch;

    update();
}

void HUDGraph::_setRoll(double roll)
{
    if (roll < -180) _roll = -180;
    else if (roll > 180) _roll = 180;
    else _roll = roll;

    update();
}

void HUDGraph::refresh()
{
    setPitch(qrand() % 180 -90);
    setRoll(qrand() % 360 - 180);

    update();
}
