#include "connect.h"
#include <fstream>
#include <ws2tcpip.h>

using std::string;

Connect::Connect(const string & host) :   mHost(host),
    mSockfd(-1)
{
}

bool Connect::isConectServer()
{
    int result = WSAStartup(MAKEWORD(2, 2), &mWsaData);
    if (result != 0)
        return false;

    struct addrinfo *servinfo;
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int status = getaddrinfo(mHost.c_str(), "http", &hints, &servinfo);
    if(status != 0)
    {
        WSACleanup();
        return false;
    }

    mSockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if(mSockfd == -1)
    {
        WSACleanup();
        return false;
    }

    if(connect(mSockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        closesocket(mSockfd);
        WSACleanup();
        return false;
    }
    else
       return true;
}

std::string Connect::getMessage(const std::string & messageToServer)
{
    string returtnMessage;
    if(isConectServer())
    {
        int len = messageToServer.length();
        int bytes_sent = send(mSockfd, messageToServer.c_str(), len, 0);
        char buf[1000];

        if((bytes_sent = recv(mSockfd, buf, 999, 0)) != -1)
            returtnMessage.assign(buf, bytes_sent);

        closesocket(mSockfd);
        WSACleanup();
    }
    return returtnMessage;
}


void Connect::saveFile(const std::string & fileName, const std::string &messageToServer)
{
    bool ifInputDataNotEmpty = !fileName.empty() && !messageToServer.empty();
    if(ifInputDataNotEmpty && isConectServer())
    {
        const int SIZEBUF = 4096;
        char buf[SIZEBUF];
        bool headerIsGone = false;
        int len = 0;
        std::ofstream file(fileName, std::ios::binary);

        send(mSockfd, messageToServer.c_str(), messageToServer.length(), 0);

        while((len = recv(mSockfd, buf, SIZEBUF-1, 0)) > 0)
        {
            if (headerIsGone) {
                file.write(buf, len);
            } else {
                char* ptr;
                buf[len] = '\0';
                ptr = strstr(buf, "\r\n\r\n");
                if (ptr != NULL) {
                    ptr += 4;
                    file.write(ptr, len - (ptr - buf));
                    headerIsGone = true;
                }
            }
        }
        file.close();
        closesocket(mSockfd);
        WSACleanup();
    }
}
