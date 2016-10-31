#ifndef CITYTOIP_H
#define CITYTOIP_H
#include <QString>
#include "connect.h"

class CityToIp
{
public:
    CityToIp();
    QString getCity();

private:
    void getLocationJson();
    void parseJson();

    QString mCity;
    QString mJson;
    Connect mConnect;
};

#endif // CITYTOIP_H
