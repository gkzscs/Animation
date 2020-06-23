#ifndef NUMBERANIMATION_H
#define NUMBERANIMATION_H

#include <QWidget>


class NumberAnimation : public QWidget
{
    Q_OBJECT

public:
    NumberAnimation(QWidget *parent = nullptr);

    void start();
    void stop();
    void setLoop(bool flag);
    void setClockwise(bool flag);
    void setPixmapCount(int count);
    void setCurrentIndex(int idx);
    void setPicture(const QString &name);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void init();

private:
    void refresh();

private:
    bool _loop;
    bool _clockwise;
    int _pixCount;
    int _curIdx;
    QVector<QPixmap> _vecPixmap;
    QTimer *_t;

};

#endif // NUMBERANIMATION_H
