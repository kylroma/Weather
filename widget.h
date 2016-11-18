#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include "settings.h"

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
    unsigned startTimer() const;

    QString mCity;
    QString mTemp;
    QString mComment;
    QString mStyle;
    QPoint mPositionMouse;
    QTimer *mTimer;
    bool mMove;
    Settings *mSettings;

private slots:
    void slotSettings();
    void slotUpdate();
    void slotAbout() const;
    void slotTimer();
};

#endif // WIDGET_H
