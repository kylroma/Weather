#include "widget.h"
#include "settingswidget.h"
#include "weather.h"
#include <QMenu>
#include <QApplication>
#include <QMessageBox>
#include "items.h"
#include "settings.h"

Widget::Widget(QWidget *parent) :   QLabel(parent),
                                    mCity("Odesa"),
                                    mTemp("0"),
                                    mComment(""),
                                    mStyle("Dark"),
                                    mPositionMouse(0,0),
                                    mMove(false)
{
    getWeather();
    setStyleWidget();
   // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);
}

void Widget::fillWidget()
{
    if(mComment.indexOf("Error") == -1)
    {
        setText("<H1>" + mCity +    "</H1>"
            "<H2>" + mComment + "</H2>"
            "<font size=7>" + mTemp +    "</font>" + "<img src=\"icon.png\">"
            );
    }
    else
        setText("<H2>" + mComment +    "</H2>");

    adjustSize();
}

void Widget::getWeather()
{
    Weather weather;

    mCity = QString::fromStdString(weather.getCity());
    mComment = QString::fromStdString(weather.getComment());
    mTemp = QString::fromStdString(weather.getTemp());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu *menu = new QMenu(this);
        menu->addAction("&Settings..", this, SLOT(slotSettings()));
        menu->addAction("&Update", this, SLOT(slotUpdate()));
        menu->addAction("&About", this, SLOT(slotAbout()));
        menu->addSeparator();
        menu->addAction("&Exit", qApp, SLOT(quit()));
        menu->exec(event->globalPos());
    }
    if(event->button() == Qt::LeftButton)
    {
        mMove = true;
        mPositionMouse = event->pos();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && mMove)
        mMove = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && mMove)
        move(event->globalPos() - mPositionMouse);
}

void Widget::slotUpdate()
{
    getWeather();
}

void Widget::slotTimer()
{
    getWeather();
}

void Widget::slotAbout()
{
    QMessageBox::about(0, "About", "Weather ver. 2.0\nAuthor Kylchitskyi Roman\ne-mail: roma1985@ukr.net");
}

void Widget::slotSettings()
{
    SettingsWidget *settingsDialog = new SettingsWidget;
    if(settingsDialog->exec() == QDialog::Accepted)
    {
        getWeather();
        setStyleWidget();
    }
    delete settingsDialog;
}

void Widget::setStyleWidget()
{
    Settings &settings = Settings::getInstance();
    Items items;
    mStyle = settings.readSettings(items.style);

    QFile file("./Style/Style" + mStyle + ".css");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    setStyleSheet(strCSS);

    fillWidget();
}
