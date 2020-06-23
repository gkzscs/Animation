#ifndef SHIPSCALE_H
#define SHIPSCALE_H

#include <QWidget>
#include <QPropertyAnimation>


class ShipScale : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _value WRITE _setValue)

public:
    ShipScale(QWidget *parent = nullptr);

    void start();
    void setValue(int v);
    void setColor(const QColor &bgColor, const QColor &lineColor);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

    void drawCircle(QPainter &p);
    void drawScale(QPainter &p);
    void drawPointer(QPainter &p);

    void _setValue(int v);

private slots:
    void refresh();

private:
    int _value;
    QColor _lineColor;
    QColor _bgColor;
    QTimer *_t;
    QPropertyAnimation *_ani;

};

#endif // SHIPSCALE_H
