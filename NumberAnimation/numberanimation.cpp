#include "numberanimation.h"
#include <QTimer>
#include <QPainter>


NumberAnimation::NumberAnimation(QWidget *parent)
    : QWidget(parent), _loop(true), _clockwise(true)
{
    init();
}

void NumberAnimation::start()
{
    connect(_t, &QTimer::timeout, this, &NumberAnimation::refresh);
    _t->start();
}

void NumberAnimation::stop()
{
    _t->stop();
    disconnect(_t, &QTimer::timeout, this, &NumberAnimation::refresh);
}

void NumberAnimation::setLoop(bool flag)
{
    _loop = flag;
}

void NumberAnimation::setClockwise(bool flag)
{
    _clockwise = flag;
}

void NumberAnimation::setPixmapCount(int count)
{
    _pixCount = count;
}

void NumberAnimation::setCurrentIndex(int idx)
{
    _curIdx = idx;
}

void NumberAnimation::setPicture(const QString &name)
{
    QPixmap pixmap(name);
    int count = 10;
    int w = pixmap.width() / count;

    for (int i = 0; i < count; ++i)
    {
        QPixmap pix = pixmap.copy(i*w, 0, w, pixmap.height());
        _vecPixmap.append(pix);
    }
}

void NumberAnimation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!_t->isActive()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPixmap pix = _vecPixmap.at(_curIdx);
    p.drawPixmap(rect(), pix);
    if (_clockwise) _curIdx = (_curIdx + 1) % 10;
    else _curIdx = (_curIdx + 9) % 10;
}

void NumberAnimation::init()
{
    _pixCount = 10;
    _curIdx = 0;
    setPicture(":/num.png");

    _t = new QTimer(this);
    _t->setInterval(500);
}

void NumberAnimation::refresh()
{
    update();
}


