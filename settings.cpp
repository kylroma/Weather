#include "settings.h"
#include <QSettings>

Settings & Settings::getInstance()
{
    static Settings instance;
    return instance;
}

Settings::Settings()
{
    readSettingsFromFile();
}

Settings::~Settings()
{
    writeSettingsToFile();
}

void Settings::writeSettings(const QString &nameParameter, const QString &parameter)
{
    if(!nameParameter.isEmpty())
        mData[nameParameter] = parameter;
}

QString Settings::readSettings(const QString &nameParemeter)
{
    if(mData.find(nameParemeter) != mData.end())
        return mData[nameParemeter];
    return "";
}

void Settings::writeSettingsToFile() const
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("/Settings");
        for(auto it: mData)
            settings.setValue(it.first, it.second);
    settings.endGroup();
}

void Settings::readSettingsFromFile()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("/Settings");
            QStringList keys = settings.allKeys();
            QStringList::Iterator it = keys.begin();
            while (it != keys.end())
            {
                mData[*it] = settings.value(*it).toString();
                ++it;
            }
    settings.endGroup();
}
