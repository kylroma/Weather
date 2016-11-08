#include "citytoip.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CityToIp::CityToIp() :  mConnect("api.sypexgeo.net"),
                        mCity(""),
                        mJson("")
{

}

QString CityToIp::getCity()
{
    getLocationJson();
    parseJson();
    return mCity;
}

void CityToIp::getLocationJson()
{
    QString message =    "GET / \n";
    mJson = QString::fromStdString(mConnect.getMessage(message.toStdString()));
}

void CityToIp::parseJson()
{

    if(!mJson.isEmpty())
    {
        QJsonDocument doc;
        doc = doc.fromJson(mJson.toUtf8());

        if(!doc.isNull())
        {
            QJsonObject obj = doc.object();
            mCity = obj["city"].toObject()["name_en"].toString();
        }
    }
}
