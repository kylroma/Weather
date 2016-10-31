#ifndef WEATHER_H
#define WEATHER_H
#include <string>
#include "connect.h"

using std::string;

class Weather
{
public:
    Weather();

    string getTemp();
    string getComment();
    string getCity();
private:
    void connectWeather(const string &city);
    string mTemp;
    string mComment;
    string mCity;
    string mIconName;
    Connect mConnect;

    void mJsonParser(const string &json);
    void saveIconFile();
};
#endif // WEATHER_H
