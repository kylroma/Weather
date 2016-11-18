#ifndef CONNECT_H
#define CONNECT_H
#include <string>

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
    struct addrinfo *mServinfo;

    bool isConectServer();
    void closeConnect() const;
};

#endif // CONNECT_H
