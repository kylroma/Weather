#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QDialog>
#include <items.h>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();
private slots:
    void slotSaveSettings();
private:
    Ui::SettingsWidget *ui;
    Items items;
};

#endif // SETTINGSWIDGET_H
