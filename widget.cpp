#include "widget.h"
#include "settingswidget.h"
#include "weather.h"
#include <QMenu>
#include <QApplication>
#include <QMessageBox>
#include "items.h"

Widget::Widget(QWidget *parent) :   QLabel(parent),
                                    mCity("Odesa"),
                                    mTemp("0"),
                                    mComment(""),
                                    mStyle("Dark"),
                                    mPositionMouse(0,0),
                                    mTimer(new QTimer),
                                    mMove(false),
                                    mSettings(&Settings::getInstance())
{
    getWeather();
    setStyleWidget();

    mTimer->start(startTimer());
    connect(mTimer, SIGNAL(timeout()), SLOT(slotTimer()));

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);
}

void Widget::fillWidget()
{
    if(mComment.indexOf("Error") == -1)
    {
            setText("<H1>" + mCity +    "</H1>"
                    "<H2>" + mComment + "</H2>"
                    "<font size=7>" + mTemp + "</font>" + "<img src=\"icon.png\">"
                    );
    }
    else
        setText("<H2>" + mComment + "</H2>");

    adjustSize();
}

void Widget::getWeather()
{
    Weather weather;

    mCity = QString::fromStdString(weather.getCity());
    mComment = QString::fromStdString(weather.getComment());
    mTemp = QString::fromStdString(weather.getTemp());

    fillWidget();
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

void Widget::slotAbout() const
{
    QMessageBox::about(0, "About", "Weather ver. 2.3\n"
                                   "Author Kylchitskyi Roman\n"
                                   "e-mail: roma1985@ukr.net");
}

void Widget::slotSettings()
{
    SettingsWidget *settingsDialog = new SettingsWidget;
    if(settingsDialog->exec() == QDialog::Accepted)
    {
        getWeather();
        mTimer->start(startTimer());

        Items items;
        if(mStyle != mSettings->readSettings(items.style))
            setStyleWidget();
    }
    delete settingsDialog;
}

void Widget::setStyleWidget()
{
    Items items;
    QString style = mSettings->readSettings(items.style);
    if(!style.isEmpty())
        mStyle = style;

    QFile file("./Style/Style" + mStyle + ".css");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    setStyleSheet(strCSS);

    fillWidget();
}

unsigned Widget::startTimer() const
{
    unsigned minutes = 30;
    Items items;
    QString minutesStr = mSettings->readSettings(items.minutes);

    if(!minutesStr.isEmpty() && minutesStr.toUInt() != 0)
        minutes = minutesStr.toUInt();

    return minutes * 1000 * 60;
}
