#include "controlsystem.h"

ControlSystem::ControlSystem(int n, Train **t)
{
    nTrains = n;
    trains = t;

    for (int i = 0; i < nTrains; i++)
    {
        trains[i]->setEnable(false);
        trains[i]->setVelocidade(125);
    }

    std::thread th = std::thread(&ControlSystem::servidor,this);
    th.detach();
}



void ControlSystem::servidor()
{
    //variáveis do servidor
    struct sockaddr_in endereco;
    int socketId;

    //variáveis relacionadas com as conexões clientes
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    int conexaoClienteId;

    //mensagem enviada pelo cliente
    Mensagem mensagem;

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
    socketId = socket(AF_INET, SOCK_STREAM, 0);

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

    //Habilitando o servidor a receber conexoes do cliente
    if ( listen( socketId, 10 ) == -1)
    {
        printf("Falha ao executar listen()\n");
        exit(EXIT_FAILURE);
    }

    //servidor ficar em um loop infinito
    while(1)
        {
        printf("Servidor: esperando conexões clientes\n");

        //Servidor fica bloqueado esperando uma conexão do cliente
        conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

        printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

        //disparar a thread
        socketHandler(conexaoClienteId,mensagem);
    }
}

void ControlSystem::socketHandler(int socketDescriptor, Mensagem mensagem)
{
    int byteslidos;

    //Verificando erros
    if ( socketDescriptor == -1)
    {
        printf("Falha ao executar accept()");
        exit(EXIT_FAILURE);
    }

    //receber uma msg do cliente
    //printf("Servidor vai ficar esperando uma mensagem\n");
    byteslidos = recv(socketDescriptor,&mensagem,sizeof(mensagem),0);

    if (byteslidos == -1)
    {
        printf("Falha ao executar recv()");
        exit(EXIT_FAILURE);
    }

    if(mensagem.tipo == 0) {
        if(mensagem.trem == 0) {
            for(int i = 0; i < 7; ++i)
                trains[i]->setEnable(false);
        }
        else {
            trains[mensagem.trem - 1]->setEnable(false);
        }
    }
    if(mensagem.tipo == 1) {
        if(mensagem.trem == 0) {
            for(int i = 0; i < 7; ++i){
                trains[i]->setEnable(true);
                trains[i]->setVelocidade(mensagem.velocidade);
            }
        }
        else {
            trains[mensagem.trem - 1]->setEnable(true);
            trains[mensagem.trem - 1]->setVelocidade(mensagem.velocidade);
        }
    }
}
