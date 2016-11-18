#ifndef SETTINGS_H
#define SETTINGS_H
#include <map>
#include <QString>

class Settings
{
public:
    static Settings & getInstance();
    void writeSettings(const QString & nameParameter, const QString & parameter);
    QString readSettings(const QString & nameParemeter);
private:
    Settings();
    Settings(const Settings &);
    Settings & operator=(Settings &);
    ~Settings();

    void writeSettingsToFile() const;
    void readSettingsFromFile();

    std::map<QString, QString> mData;
};


#endif // SETTINGS_H


