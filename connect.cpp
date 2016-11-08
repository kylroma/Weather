#include "connect.h"
#include <unistd.h> // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>

using std::string;

Connect::Connect(const string & host) :  mHost(host),
                                         mSockfd(-1),
                                         mServinfo(nullptr)
{
}

bool Connect::isConectServer()
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int status = getaddrinfo(mHost.c_str(), "http", &hints, &mServinfo);
    if(status != 0)
        return false;

    mSockfd = socket(mServinfo->ai_family, mServinfo->ai_socktype, mServinfo->ai_protocol);
    if(mSockfd == -1)
    {
        freeaddrinfo(mServinfo);
        return false;
    }

    status = connect(mSockfd, mServinfo->ai_addr, mServinfo->ai_addrlen);
    if(status == -1)
    {
        closeConnect();
        return false;
    }

return true;
}

std::string Connect::getMessage(const std::string & messageToServer)
{
    string returnMessage;
    if(isConectServer())
    {
        int len = messageToServer.length();
        int bytes_sent = send(mSockfd, messageToServer.c_str(), len, 0);
        const int SIZEBUF = 2048;
        char buf[SIZEBUF];

        if((bytes_sent = recv(mSockfd, buf, SIZEBUF-1, 0)) != -1)
            returnMessage.assign(buf, bytes_sent);

        closeConnect();
    }
    return returnMessage;
}


void Connect::saveFile(const std::string & fileName, const std::string &messageToServer)
{
    bool ifInputDataNotEmpty = !fileName.empty() && !messageToServer.empty();
    if(ifInputDataNotEmpty && isConectServer())
    {
        const int SIZEBUF = 4096;
        char buf[SIZEBUF];
        int len = 0;
        std::ofstream file(fileName, std::ios::binary);

        send(mSockfd, messageToServer.c_str(), messageToServer.length(), 0);

        while((len = recv(mSockfd, buf, SIZEBUF-1, 0)) > 0)
        {
            file.write(buf, len);
        }
        file.close();
        closeConnect();
    }
}

void Connect::closeConnect()
{
    close(mSockfd);
    freeaddrinfo(mServinfo);
}
