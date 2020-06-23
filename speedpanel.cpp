#include "speedpanel.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QDebug>

SpeedPanel::SpeedPanel(QWidget *parent)
    : QWidget(parent), _value(50), _bgColor(Qt::gray), _fontColor(Qt::red)
{
    init();
}

void SpeedPanel::start()
{
    connect(_t, &QTimer::timeout, this, &SpeedPanel::refresh);
    _t->setInterval(1000);
    _t->start();
}

void SpeedPanel::setValue(int v)
{
    _ani->setStartValue(_value);
    _ani->setEndValue(v);
    _ani->start();

    if (v < 0) _value = 0;
    else if (v > 200) _value = 200;
    else _value = v;

    _number->setDigitCount(v);
}

void SpeedPanel::setColor(const QColor &bgColor, const QColor &fontColor)
{
    _bgColor = bgColor;
    _fontColor = fontColor;
}

void SpeedPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    _wgt->setGeometry(width()/2-50, height()/2+50, 100, 50);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    drawFrame(p);
    drawScale(p);
    drawText(p);
    drawPointer(p);
}

void SpeedPanel::init()
{
    _t = new QTimer(this);
    _ani = new QPropertyAnimation(this, "_value");
    _ani->setDuration(500);

    // Initialize the QLCDNumber and QLabel objects
    _number = new QLCDNumber(this);
    _lab = new QLabel("KM", this);
    _number->setDecMode();
    _number->setSegmentStyle(QLCDNumber::Flat);
    QWidget *wgt = new QWidget(this);
    QHBoxLayout *hl = new QHBoxLayout(wgt);
    hl->addWidget(_number);
    hl->addWidget(_lab);
    wgt->show();
    _wgt = wgt;
}

void SpeedPanel::drawFrame(QPainter &p)
{
    p.save();

    int len = (width() < height() ? width() : height()) - 50;

    QLinearGradient lg(0, 0, width(), height());
    lg.setColorAt(0.0, QColor(0, 0, 0));
    lg.setColorAt(0.5, QColor(188, 188, 188));
    lg.setColorAt(1.0, QColor(255, 255, 255));

    QPen pen;
    pen.setColor(_bgColor);
    pen.setWidth(20);
    QBrush brush(lg);

    p.setPen(pen);
    p.setBrush(brush);
    p.drawEllipse(25, height()/2-len/2, len, len);

    p.restore();
}

void SpeedPanel::drawScale(QPainter &p)
{
    p.save();

    const double totalAngle = 250.0;
    const int count = 200 / 20;
    QPoint center(width()/2, height()/2);
    int len = (width() < height() ? width() : height()) - 50;
    int radius = len/2 - 20;

    QPen pen(_fontColor);

    // Draw biggest scales
    p.translate(width()/2, height()/2);
    p.rotate(30);
    for (int i = 0; i < count+1; ++i)
    {
        pen.setWidth(4);
        p.setPen(pen);
        p.drawLine(radius-20, 0, radius, 0);
        p.rotate(-totalAngle/count);
    }

    p.rotate(totalAngle/count + totalAngle/count/2);
    for (int i = 0; i < count; ++i)
    {
        pen.setWidth(2);
        p.setPen(pen);
        p.drawLine(radius-10, 0, radius, 0);
        p.rotate(totalAngle/count);
    }

    p.restore();
}

void SpeedPanel::drawText(QPainter &p)
{
    p.save();

    const double totalAngle = 250.0;
    const int count = 200 / 20;
    QPoint center(width()/2, height()/2);
    int len = (width() < height() ? width() : height()) - 50;
    int radius = len/2 - 20;

    QPen pen(_fontColor);
    p.setPen(pen);

    // Draw scale text
    p.translate(width()/2, height()/2);
    p.rotate(30);
    for (int i = 0; i < count+1; ++i)
    {
        QRect r(radius-60, -20, 40, 40);
        int num = i * 200 / count;
        p.drawText(r, Qt::AlignCenter, QString::number(num));
        p.rotate(-totalAngle/count);
    }

    p.restore();

    p.save();
    // Draw speed text
    pen.setColor(_bgColor);
    p.setFont(QFont("楷体", 18, 10));
    p.setPen(pen);

    QString speed = QString("%1 Km/h").arg(_value);
    p.drawText(QRect(width()/2-50, height()/2-80, 100, 50), Qt::AlignCenter, speed);

    p.restore();
}

void SpeedPanel::drawPointer(QPainter &p)
{
    p.save();

    const double totalAngle = 250.0;
    QPoint center(width()/2, height()/2);
    int len = (width() < height() ? width() : height()) - 50;
    int radius = len/2 - 20;
    double angle = 240.0 * _value / totalAngle;

    QBrush brush(_bgColor);
    p.setBrush(brush);

    p.translate(width()/2, height()/2);
    p.rotate(-angle);

    // Draw pointer
    QPointF points[3];
    points[0] = QPointF(0, -5);
    points[1] = QPointF(0, 5);
    points[2] = QPointF(radius-60, 0);
    p.drawPolygon(points, 3);

    // Draw circle
    p.drawEllipse(-5, -5, 10, 10);

    p.restore();
}

void SpeedPanel::_setValue(int v)
{
    _value = v;
    repaint();
}

void SpeedPanel::refresh()
{
    setValue(qrand() % 200);
    repaint();
}



