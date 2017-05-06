#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <iostream>
#include <vector>
#include "include/main.h"
#include "include/game.h"

using namespace std; 
 
#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325
 
void socketHandler(int socketDescriptor, char* mensagem, Game* g, int* oldValue)
{
    Mensagem m;

    char* chars_array = strtok(mensagem, ",");
    m.pot = atoi(chars_array);
    chars_array = strtok(NULL, ",");
    m.button = atoi(chars_array);
    chars_array = strtok(NULL, ",");
    m.ldr = atoi(chars_array);

    fflush(stdout);
    game(m, g, *oldValue);

    *oldValue = m.pot; 

    close(socketDescriptor);
}
 
 
int main(int argc, char *argv[])
{
    //variáveis do servidor
    struct sockaddr_in endereco;
    int socketId;
 
    //variáveis relacionadas com as conexões clientes
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    int conexaoClienteId;
 
    //mensagem enviada pelo cliente
    char *mensagem = new char[MAXMSG+1];

    int oldValue = 2000;

    Game g;
    fflush(stdout); 
    g.gameInit();
 
    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    //endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_addr.s_addr = inet_addr("192.168.7.1");
 
    /*
     * Criando o Socket
     *
     * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
     * PARAM2: SOCK_STREAM ou SOCK_DGRAM
     * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente
    */
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
 
    //Verificar erros
    if (socketId == -1)
    {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }
 
    //Conectando o socket a uma porta. Executado apenas no lado servidor
    if ( bind (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
    {
        printf("Falha ao executar bind()\n");
        exit(EXIT_FAILURE);
    }

    //servidor ficar em um loop infinito
    while(1)
    {
        //Servidor fica bloqueado esperando uma conexão do cliente
        //conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );
        recvfrom(socketId, mensagem, MAXMSG+1, 0, (struct sockaddr *) &enderecoCliente, &tamanhoEnderecoCliente);
        
        sendto(socketId, mensagem , strlen(mensagem), 0, (struct sockaddr *) &enderecoCliente, tamanhoEnderecoCliente);
        
        //disparar a thread
        fflush(stdout); 
        thread t(socketHandler,conexaoClienteId,mensagem,&g, &oldValue);
        t.detach();
    }
 
    return 0;
}
