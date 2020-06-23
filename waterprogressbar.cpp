#include "waterprogressbar.h"
#include <QPainter>


WaterProgressBar::WaterProgressBar(QWidget *parent)
    : QWidget(parent), _value(30), _minValue(0), _maxValue(100), _radius(200)
{
    init();
}

void WaterProgressBar::start()
{
    connect(_t, &QTimer::timeout, this, &WaterProgressBar::refresh);
    _t->setInterval(1000);
    _t->start();
}

void WaterProgressBar::stop()
{
    disconnect(_t, &QTimer::timeout, this, &WaterProgressBar::refresh);
    _t->stop();
}

void WaterProgressBar::setValue(int v)
{
    _ani->setStartValue(_value);
    _ani->setEndValue(v);
    _ani->start();

    if (v < _minValue) _value = _minValue;
    else if (v > _maxValue) _value = _maxValue;
    else _value = v;
}

void WaterProgressBar::setRange(int min, int max)
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

void WaterProgressBar::setRadius(int r)
{
    _radius = r;
}

void WaterProgressBar::setColor(const QColor &bgColor, const QColor &fontColor)
{
    _bgColor = bgColor;
    _fontColor = fontColor;
}

void WaterProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    drawBorder();
    drawWater();
    drawText();
}

void WaterProgressBar::init()
{
    _bgColor = QColor(Qt::blue);
    _fontColor = QColor(Qt::green);
    _t = new QTimer(this);

    _ani = new QPropertyAnimation(this, "_value");
    _ani->setDuration(500);
    _ani->setEasingCurve(QEasingCurve::OutQuad);
}

void WaterProgressBar::drawWater()
{
    int len = (width() > height() ? height() : width()) - 50;
    QPainter p(this);
    QPainterPath path;

    // Calculate the angle
    double startAngle = 270.0 - _value * 180 / _maxValue;
    double endAngle = 360.0 - (startAngle - 90) * 2;

    p.setBrush(_bgColor);
    path.addEllipse(QRect(25, height()/2-len/2, len, len));
    p.drawPath(path);

    p.setBrush(Qt::black);
    p.setRenderHints(QPainter:: Antialiasing | QPainter::SmoothPixmapTransform, true);
    path.arcMoveTo(25, height()/2-len/2, len, len, startAngle);
    path.arcTo(QRect(25, height()/2-len/2, len, len), startAngle, endAngle);
    p.drawPath(path);
}

void WaterProgressBar::drawBorder()
{
    int len = (width() > height() ? height() : width()) - 50;
    QPainter p(this);
    QPen pen(Qt::gray);
    p.setPen(pen);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawEllipse(25, height()/2-len/2, len, len);
}

void WaterProgressBar::drawText()
{
    QPainter p(this);
    QPen pen(_fontColor);
    QFont font("楷体", 72, 10);
    pen.setWidth(8);
    p.setPen(pen);
    p.setFont(font);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawText(rect(), Qt::AlignCenter, QString::number(_value));
}

int WaterProgressBar::_getValue() const
{
    return _value;
}

void WaterProgressBar::_setValue(int v)
{
    if (v < _minValue) _value = _minValue;
    else if (v > _maxValue) _value = _maxValue;
    else _value = v;

    repaint();
}

void WaterProgressBar::refresh()
{
    setValue(qrand() % _maxValue);
    repaint();
}



