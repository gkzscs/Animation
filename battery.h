#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>


class Battery : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _value WRITE _setValue)

public:
    Battery(QWidget *parent = nullptr);

    void start();
    void setValue(int v);
    void setColor(const QColor &bgColor);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

    void drawBorder(QPainter *p);
    void drawCapacity(QPainter *p);
    void drawText(QPainter *p);

private:
    void _setValue(int v);

private slots:
    void refresh();

private:
    int _value;
    QTimer *_t;
    QPropertyAnimation *_ani;
    QColor _bgColor;

};

#endif // BATTERY_H
