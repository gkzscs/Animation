#ifndef SPEEDPANEL_H
#define SPEEDPANEL_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QLCDNumber>
#include <QLabel>


class SpeedPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _value WRITE _setValue)

public:
    SpeedPanel(QWidget *parent = nullptr);

    void start();
    void setValue(int v);
    void setColor(const QColor &bgColor, const QColor &fontColor);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

    void drawFrame(QPainter &p);
    void drawScale(QPainter &p);
    void drawText(QPainter &p);
    void drawPointer(QPainter &p);

private:
    void _setValue(int v);

private slots:
    void refresh();

private:
    int _value;
    QColor _bgColor;
    QColor _fontColor;
    QTimer *_t;
    QPropertyAnimation *_ani;
    QLCDNumber *_number;
    QLabel *_lab;
    QWidget *_wgt;

};

#endif // SPEEDPANEL_H
