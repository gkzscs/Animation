#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsItem>


class Ship : public QGraphicsItem
{
public:
    Ship();

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    virtual void advance(int phase) override;

private:
    void init();

private:
    qreal _angle;
    qreal _speed;
    qreal _dir;
    QColor _color;

};

#endif // SHIP_H
