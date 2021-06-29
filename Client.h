#ifndef IDE_RAMCLIENT_H
#define IDE_RAMCLIENT_H


#include <arpa/inet.h>
//#include <string>
#include "Client.h"
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

class Client {

private:
    char buffer[1024];
    struct sockaddr_in addressSender;
    struct sockaddr_in addressinit;
    struct sockaddr_in addressReader;

    int opt = 1;
    int addrlen = sizeof(addressSender);
    int sender,reader,init;
    char* ok = "xx";
    //std::string direction;

public:
    Client();
    void initSender(std::string image);
    std::string createSender(std::string direction);
    std::string createReader();
    //static Client *GetInstance();
};


#endif //IDE_RAMCLIENT_H