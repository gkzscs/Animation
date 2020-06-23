#ifndef WATERPROGRESSBAR_H
#define WATERPROGRESSBAR_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>


class WaterProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _value READ _getValue WRITE _setValue)

public:
    WaterProgressBar(QWidget *parent = nullptr);

    void start();
    void stop();
    void setValue(int v);
    void setRange(int min, int max);
    void setRadius(int r);
    void setColor(const QColor &bgColor, const QColor &fontColor);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

    void drawWater();
    void drawBorder();
    void drawText();

    int _getValue() const;
    void _setValue(int v);

private slots:
    void refresh();

private:
    int _value;
    int _minValue;
    int _maxValue;
    int _radius;
    QColor _bgColor;
    QColor _fontColor;
    QTimer *_t;
    QPropertyAnimation *_ani;

};

#endif // WATERPROGRESSBAR_H
