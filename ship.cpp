#include "ship.h"
#include <QGraphicsScene>
#include <QPainter>

static const double Pi = 3.1415926;
static const double TwoPi = Pi * 2;


static qreal normalizeAngle(qreal angle)
{
    while (angle < 0) angle += TwoPi;
    while (angle > TwoPi) angle -= TwoPi;

    return angle;
}

Ship::Ship()
{
    init();
}

QRectF Ship::boundingRect() const
{
    return QRectF(0, 0, 30, 80);
}

QPainterPath Ship::shape() const
{
    QVector<QPoint> points = { QPoint(0, -150), QPoint(0, 15), QPoint(80, 0) };
    QPainterPath path;
    path.addPolygon(QPolygonF(points));
    return path;
}

void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static QPoint points[] = { QPoint(0, -15), QPoint(0, 15), QPoint(80, 0) };
    _color = (scene()->collidingItems(this).isEmpty() ? Qt::darkCyan : Qt::red);
    painter->setBrush(_color);
    painter->drawPolygon(points, 3);
}

void Ship::advance(int step)
{
    if (!step)
    return;
    // Don't move too far away
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = ::acos(lineToCenter.dx() / lineToCenter.length());
        if (lineToCenter.dy() < 0)
            angleToCenter = TwoPi - angleToCenter;
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            _angle += (_angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            _angle += (_angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(_angle) < 0) {
        _angle += 0.25;
    } else if (::sin(_angle) > 0) {
        _angle -= 0.25;
    }

    // Try not to crash with any other ships
    QList<QGraphicsItem *> dangerShips = scene()->items(QPolygonF()
                                                       << mapToScene(0, 0)
                                                       << mapToScene(-30, -50)
                                                       << mapToScene(30, -50));
    foreach (QGraphicsItem *item, dangerShips) {
        if (item == this)
            continue;

        QLineF lineToShip(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToShip = ::acos(lineToShip.dx() / lineToShip.length());
        if (lineToShip.dy() < 0)
            angleToShip = TwoPi - angleToShip;
        angleToShip = normalizeAngle((Pi - angleToShip) + Pi / 2);

        if (angleToShip >= 0 && angleToShip < Pi / 2) {
           // Rotate right
           _angle += 0.5;
       } else if (angleToShip <= TwoPi && angleToShip > (TwoPi - Pi / 2)) {
           // Rotate left
           _angle -= 0.5;
       }
    }
    // Add some random movement
    if (dangerShips.size() > 1 && (qrand() % 10) == 0) {
        if (qrand() % 1)
            _angle += (qrand() % 100) / 500.0;
        else
            _angle -= (qrand() % 100) / 500.0;
    }

    _speed += (-50 + qrand() % 100) / 100.0;

    qreal dx = ::sin(_angle) * 10;
    _dir = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(_speed) * 3)));
}

void Ship::init()
{
    _angle = 0;
    _speed = 10;
    _dir = 0;
    _color = QColor(188, 233, 144);

    setRotation(qrand() % 360);
}
