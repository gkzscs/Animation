#ifndef DOT_H
#define DOT_H

#include <QWidget>

class Dot : public QWidget
{
    Q_OBJECT

public:
    Dot(QWidget *parent = nullptr);

    void setColor(const QColor &color);
    void setRadius(int r);
    void setPos(int x, int y);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QColor _bgColor;
    int _radius;

};

#endif // DOT_H
