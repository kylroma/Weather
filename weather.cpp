#include "weather.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <map>
#include "citytoip.h"
#include "settings.h"
#include "items.h"

using std::string;

Weather::Weather() : mConnect("api.openweathermap.org")
{
    Settings &settings = Settings::getInstance();
    Items items;
    string city;

    if(settings.readSettings(items.cityToIP) == "true")
    {
        CityToIp toIp;
        city = toIp.getCity().toStdString();
    }
    else
        city = settings.readSettings(items.city).toStdString();

    connectWeather(city);
}

void Weather::connectWeather(const string &city)
{
    string message =    "GET /data/2.5/weather/?q=" + city +
                    "&units=metric&APPID=f35aabad9d11c1c2f787fad11e074b89\r\n";
    string weatherJson = mConnect.getMessage(message);

    if(!weatherJson.empty())
    {
        mJsonParser(weatherJson);
        saveIconFile();
    }
    else
        mComment = "Error: connect";
}

void Weather::mJsonParser(const string &json)
{
    if(!json.empty())
    {
        QJsonDocument doc;
        doc = doc.fromJson(json.c_str());

        if(!doc.isNull())
        {
            QJsonObject obj = doc.object();
            mComment = obj["message"].toString().toStdString();
            if(mComment.empty())
            {
                mCity = obj["name"].toString().toStdString() + ", ";
                mCity += obj["sys"].toObject()["country"].toString().toStdString();
                mComment = obj["weather"].toArray()[0].toObject()["description"].toString().toStdString();
                mIconName = obj["weather"].toArray()[0].toObject()["icon"].toString().toStdString();
                mTemp = std::to_string((int) obj["main"].toObject()["temp"].toDouble());
                mTemp += " \xC2\xB0\C";
            }
        }
    }
}

void Weather::saveIconFile()
{
    string messageToServer = "GET /img/w/" + mIconName + "\r\n"\
                     "Host: api.openweathermap.org\r\n\r\n";
    string fileName = "icon.png";
    mConnect.saveFile(fileName, messageToServer);
}

string Weather::getTemp()
{
    return mTemp;
}

string Weather::getComment()
{
    return mComment;
}

string Weather::getCity()
{
    return mCity;
}
