#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QMouseEvent>

class Widget : public QLabel
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

private:
    void fillWidget();
    void getWeather();
    void setStyleWidget();
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

    QString mCity;
    QString mTemp;
    QString mComment;
    QString mStyle;
    QPoint mPositionMouse;
    bool mMove;

private slots:
    void slotSettings();
    void slotUpdate();
    void slotAbout();
    void slotTimer();
};

#endif // WIDGET_H
