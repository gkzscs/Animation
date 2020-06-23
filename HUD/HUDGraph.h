#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>


class HUDGraph : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double _pitch WRITE _setPitch)
    Q_PROPERTY(double _roll WRITE _setRoll)

public:
    HUDGraph(QWidget *parent = nullptr);

    void start();
    void setPitch(double pitch);
    void setRoll(double roll);
    void setColor(const QColor &skyColor, const QColor &groundColor);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    void init();

    void drawBackground(QPainter &p);
    void drawPitch(QPainter &p);
    void drawRoll(QPainter &p);

private:
    void _setPitch(double pitch);
    void _setRoll(double roll);

private slots:
    void refresh();

private:
    double _pitch;
    double _roll;
//    double _yaw;
    QColor _skyColor;
    QColor _groundColor;
    QTimer *_t;
    QPropertyAnimation *_aniPitch;
    QPropertyAnimation *_aniRoll;

};
