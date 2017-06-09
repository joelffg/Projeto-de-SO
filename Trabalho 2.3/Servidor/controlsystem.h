#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "train.h"
#include <QObject>

#include <thread>
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <iostream>
#include <vector>

using namespace std;

#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325

class ControlSystem : public QObject
{
    Q_OBJECT
public:
    ControlSystem(int, Train**);

    typedef struct{
        int tipo;
        int trem;
        int velocidade;
    }Mensagem;
private:
    int nTrains;
    Train **trains;

    void servidor();
    void socketHandler(int socketDescriptor, Mensagem mensagem);
};

#endif // CONTROLSYSTEM_H
