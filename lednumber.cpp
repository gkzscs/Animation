#include "lednumber.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>


LEDNumber::LEDNumber(QWidget *parent)
    : QWidget(parent), _bgColor(Qt::blue), _font("楷体"), _content(52)
{

}

void LEDNumber::start()
{
    _t = new QTimer(this);
    connect(_t, &QTimer::timeout, this, &LEDNumber::refresh);
    _t->setInterval(1000);
    _t->start();
}

void LEDNumber::stop()
{
    disconnect(_t, &QTimer::timeout, this, &LEDNumber::refresh);
    _t->stop();
}

void LEDNumber::setColor(const QColor &bgColor, const QColor &fontColor)
{
    _bgColor = bgColor;
    _fontColor = fontColor;
}

void LEDNumber::setFont(const QFont &font)
{
    _font = font;
}

void LEDNumber::setContent(const QString &content)
{
    _content = content;
}

void LEDNumber::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    draw();
}

void LEDNumber::draw()
{
    // Draw background
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(_bgColor);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    p.fillPath(path, _bgColor);
    p.drawPath(path);

    //Draw middle line
    QPen pen(Qt::white, 5);
    p.setPen(pen);
    p.drawLine(0, height()/2, width(), height()/2);

    // Draw content
    p.setPen(_fontColor);
    p.setFont(QFont("楷体", 80, 36));
    p.drawText(rect(), Qt::AlignCenter, _content);
}

void LEDNumber::refresh()
{
    int num = qrand() % 1024;
    setContent(QString::number(num));

    repaint();
}
