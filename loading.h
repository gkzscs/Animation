#ifndef Loading_H
#define Loading_H

#include <QWidget>
#include "dot.h"


class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui { class Loading; }
QT_END_NAMESPACE

class Loading : public QWidget
{
    Q_OBJECT

public:
    Loading(QWidget *parent = nullptr);
    virtual ~Loading() override;

    void start();
    void stop();
    void setCount(int n);
    void setRadius(int min, int max);
    void setInterver(int interval);
    void setColor(const QColor &color);

private:
    void calculate();

private slots:
    void refresh();

private:
    Ui::Loading *ui;

    QVector<Dot *> _vecDots;
    QVector<int> _vecRadius;
    QVector<QPoint> _vecCenters;
    int _idx;
    int _count;
    int _maxRadius;
    int _minRadius;
    int _interval;
    QColor _color;
    QTimer *_t;

};
#endif // Loading_H
