#include "settingswidget.h"
#include "ui_settingswidget.h"
#include "settings.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
                                                 QDialog(parent,
                                                         Qt::WindowTitleHint |
                                                         Qt::WindowSystemMenuHint),
                                                 ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    Settings &settings = Settings::getInstance();

    ui->lineCity->setText(settings.readSettings(items.city));
    ui->comboBoxStyle->setCurrentText(settings.readSettings(items.style));
    QString cityToIp = settings.readSettings(items.cityToIP);
    ui->checkBoxCityToIp->setChecked(cityToIp == "true");
    ui->spinBoxMinutes->setValue((settings.readSettings(items.minutes)).toUInt());

    connect(ui->buttonBoxOkCancel, SIGNAL(accepted()), this, SLOT(slotSaveSettings()));
    connect(ui->buttonBoxOkCancel, SIGNAL(rejected()), this, SLOT(close()));

    setFixedSize(250, 207);
}

void SettingsWidget::slotSaveSettings()
{
    Settings &settings = Settings::getInstance();
    settings.writeSettings(items.city, ui->lineCity->text());
    settings.writeSettings(items.style, ui->comboBoxStyle->currentText());
    settings.writeSettings(items.minutes, QString::number(ui->spinBoxMinutes->value()));
    settings.writeSettings(items.cityToIP, ui->checkBoxCityToIp->isChecked() ? "true" : "false");
    accept();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}
