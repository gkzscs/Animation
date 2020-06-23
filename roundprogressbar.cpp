#include "roundprogressbar.h"
#include <QPainter>
#include <QTimer>
#include <QPropertyAnimation>


RoundProgressBar::RoundProgressBar(QWidget *parent)
    : QWidget(parent), _fontColor(Qt::blue), _outColor(Qt::green), _inColor(Qt::gray),
      _interval(1000), _value(30), _minValue(0), _maxValue(100), _valueType(ValueRange)
{

}

void RoundProgressBar::start()
{
    _t = new QTimer(this);
    connect(_t, &QTimer::timeout, this, &RoundProgressBar::refresh);
    _t->setInterval(_interval);
    _t->start();
}

void RoundProgressBar::stop()
{
    _t->stop();
    disconnect(_t, &QTimer::timeout, this, &RoundProgressBar::refresh);
}

void RoundProgressBar::setInterval(int interval)
{
    _interval = interval;
}

void RoundProgressBar::setValueType(ValueType type)
{
    _valueType = type;
}

void RoundProgressBar::setRange(int min, int max)
{
    if (min > max)
    {
        int tmp = min;
        min = max;
        max = tmp;
    }

    _minValue = min;
    _maxValue = max;
}

void RoundProgressBar::setValue(int v)
{
    QPropertyAnimation* animation=new QPropertyAnimation(this, "_value");
    animation->setDuration(500);
    animation->setStartValue(_value);
    animation->setEndValue(v);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start();
}

void RoundProgressBar::setFontColor(const QColor &color)
{
    _fontColor = color;
}

void RoundProgressBar::setInColor(const QColor &color)
{
    _inColor = color;
}

void RoundProgressBar::setOutColor(const QColor &color)
{
    _outColor = color;
}

void RoundProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    drawValue();
    drawBound();
    drawStartDot();
}

void RoundProgressBar::drawValue()
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPen pen(_fontColor);
    pen.setWidth(10);
    p.setFont(QFont("楷体", 24, 10));
    p.setPen(pen);

    p.drawText(rect(), Qt::AlignCenter, QString("%1/%2").arg(_value).arg(_maxValue));
}

void RoundProgressBar::drawBound()
{
    int len = (width() < height() ? width() : height()) - 50;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPen pen(_inColor);
    pen.setWidth(10);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    p.setPen(pen);
    p.drawArc(QRect(width()/2-len/2, height()/2-len/2, len, len), 0, 360*16);

    pen.setColor(_outColor);
    pen.setWidth(20);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    p.setPen(pen);
    int spanAngle = 360 * (_value-_minValue) / (_maxValue-_minValue);
    p.drawArc(QRect(width()/2-len/2, height()/2-len/2, len, len), 0, spanAngle*16);
}

void RoundProgressBar::drawStartDot()
{
    if (_value/_maxValue < 3/100) return;

    int len = (width() < height() ? width() : height()) - 50;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::white);
    QBrush brush(Qt::yellow);

    p.setPen(pen);
    p.setBrush(brush);
    p.drawEllipse(QRect(len+17, height()/2-12, 15, 15));
}

void  RoundProgressBar::_setValue(int v)
{
    if (v > _maxValue) v = _maxValue;
    else if (v < _minValue) v = _minValue;
    else _value = v;

    repaint();
}

int RoundProgressBar::_getValue()
{
    return _value;
}

void RoundProgressBar::refresh()
{
    setValue(qrand() % _maxValue);
    repaint();
}
