#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QWidget>


class RoundProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int _value READ _getValue WRITE _setValue)

public:
    enum ValueType
    {
        Percent,
        ValueRange
    };

public:
    RoundProgressBar(QWidget *parent = nullptr);

    void start();
    void stop();
    void setValueType(ValueType type);
    void setInterval(int interval);
    void setRange(int min, int max);
    void setValue(int v);
    void setFontColor(const QColor &color);
    void setInColor(const QColor &color);
    void setOutColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void drawValue();
    void drawBound();
    void drawStartDot();

private:
    void _setValue(int v);
    int _getValue();

private slots:
    void refresh();

private:
    QTimer *_t;
    QColor _fontColor;
    QColor _outColor;
    QColor _inColor;
    int _interval;
    int _value;
    int _minValue;
    int _maxValue;
    ValueType _valueType;

};

#endif // ROUNDPROGRESSBAR_H
