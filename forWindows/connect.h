#ifndef CONNECT_H
#define CONNECT_H
#include <string>
#include <winsock2.h>

using std::string;

class Connect
{
public:
    Connect(const string& host);

    std::string getMessage(const string & messageToServer);
    void saveFile(const string & fileName, const string & messageToServer);
private:
    int mSockfd;
    string mHost;
    WSADATA mWsaData;
    bool isConectServer();
};

#endif // CONNECT_H
