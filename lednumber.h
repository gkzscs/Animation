#ifndef LEDNUMBER_H
#define LEDNUMBER_H

#include <QWidget>


class LEDNumber : public QWidget
{
    Q_OBJECT

public:
    LEDNumber(QWidget *parent = nullptr);

    void start();
    void stop();
    void setColor(const QColor &bgColor, const QColor &fontColor);
    void setFont(const QFont &font);
    void setContent(const QString &content);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void draw();

private slots:
    void refresh();

private:
    QTimer *_t;
    QColor _bgColor;
    QColor _fontColor;
    QFont _font;
    QString _content;

};

#endif // LEDNUMBER_H
