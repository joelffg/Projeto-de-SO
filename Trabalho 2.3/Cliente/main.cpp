#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <cstring>      //memset
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <thread>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "cursor.h"
#include "semaphore.h"
#include "apiGPIO.h"

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"
#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325
 
class Mensagem {
    public:
        int tipo;
        int trem;
        int velocidade;
        Mensagem();
};
 
Mensagem::Mensagem()
{
}

Semaphore* sem;

using namespace std;

void printInterface(string);
void signalHandlerFunction (int);
void gpioControl(int*);
void potControl(int*);

bool buttonIsPressed(int gpio){
	setDirection(gpio, "in");
	
	if(getValue(gpio) == 1)
		return true;
	else
		return false;
}

int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

void sendMessage(){
}

int main (int argc, char* argv[])
{
	
		signal(SIGINT, signalHandlerFunction);
		system("clear");
		system("stty -icanon -echo");

		sem = new Semaphore(1220, 1);
		
		printInterface("192.168.7.1");
		
		int velocity;

		thread tGPIO = thread(gpioControl, &velocity);
		thread tPot = thread(potControl, &velocity);

		tGPIO.join();
		tPot.join();

		delete sem;
		return 0;
}

void printInterface(string ip)
{
	Cursor c;
	c.saveCursor();
	c.moveCursor(1,0);
	cout<<"-- Projeto2.3: Trens e Semáforos --" << endl;
	c.resumeCursor();
	c.moveCursor(4,1);
	cout<<"IP do Servidor: " << ip << endl;
	c.resumeCursor();
	c.moveCursor(4,2);
	cout<<"Status: Desconectado" << endl;
	c.resumeCursor();
	c.moveCursor(2,4);
	cout<<"* Trem: TODOS" << endl;
	c.resumeCursor();
	c.moveCursor(2,5);
	cout<<"* Vel:" << endl;
	c.resumeCursor();
	c.moveCursor(4,7);
	cout<<"Ligar/Setar Velocidade" << endl;
	c.resumeCursor();
	c.moveCursor(4,8);
	cout<<"Parar" << endl;
	c.resumeCursor();
	c.moveCursor(4,9);
	cout<<"Mudar Trem" << endl;
	c.resumeCursor();
	c.moveCursor(4,11);
	cout<<"Conectar/Desconectar" << endl;
	c.resumeCursor();
	c.moveCursor(1,7);
	cout<<"->"<< endl;
	c.resumeCursor();

	fflush(stdout);
}

void gpioControl(int* vel)
{
    struct sockaddr_in endereco;
    int socketId;
 
    Mensagem mensagem;
    mensagem.tipo = 0;
    mensagem.trem = 1;
    mensagem.velocidade = 0;
    int bytesenviados;
    bool connected = false;

    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    endereco.sin_addr.s_addr = inet_addr("192.168.7.1");

	Cursor c;
	int trem = 0, selector = 0;

	while(1)
	{

		if(buttonIsPressed(115))
		{
			sem->P();

			switch (selector)
			{
				case 0:
					selector = 3;
					c.saveCursor();
					c.moveCursor(1,7);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,11);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				case 1:
					selector = 0;
					c.saveCursor();
					c.moveCursor(1,8);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,7);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				case 2:
					selector = 1;
					c.saveCursor();
					c.moveCursor(1,9);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,8);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				case 3:
					selector = 2;
					c.saveCursor();
					c.moveCursor(1,11);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,9);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				default:
					break;
			}

			sem->V();

			this_thread::sleep_for(chrono::milliseconds(250));
		}
		if(buttonIsPressed(7))
		{
			sem->P();
			switch (selector)
			{
				case 0:
					selector = 1;
					c.saveCursor();
					c.moveCursor(1,7);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,8);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				case 1:
					selector = 2;
					c.saveCursor();
					c.moveCursor(1,8);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,9);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				case 2:
					selector = 3;
					c.saveCursor();
					c.moveCursor(1,9);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,11);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				case 3:
					selector = 0;
					c.saveCursor();
					c.moveCursor(1,11);
					cout<<"  "<<endl;
					c.resumeCursor();
					c.moveCursor(1,7);
					cout<<"->"<<endl;
					c.resumeCursor();
					fflush(stdout);
					break;
				default:
					break;
			}
			sem->V();
			this_thread::sleep_for(chrono::milliseconds(250));
		}
		if(buttonIsPressed(20))
		{
			switch (selector)
			{
				case 0:
					/* Envia a mensagem com o tipo (0 ou 1), trem (trem) e a velocidade (*vel)
					 */
				    mensagem.tipo = 1;
				    mensagem.trem = trem;
				    mensagem.velocidade = *vel;

				    if(connected){
 
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
				    	//Conectando o socket cliente ao socket servidor
					    if ( connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
					    {
					        printf("Falha ao executar connect()\n");
					        exit(EXIT_FAILURE);
					    }

					    bytesenviados = send(socketId,&mensagem,sizeof(mensagem),0);
					 
					    if (bytesenviados == -1)
					    {
					        printf("Falha ao executar send()");
					        exit(EXIT_FAILURE);
					    }
						close(socketId);
					}
					break;
				case 1:
				    mensagem.tipo = 0;
				    mensagem.trem = trem;
				    mensagem.velocidade = *vel;

				    if(connected){
 
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
				    	//Conectando o socket cliente ao socket servidor
					    if ( connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
					    {
					        printf("Falha ao executar connect()\n");
					        exit(EXIT_FAILURE);
					    }

					    bytesenviados = send(socketId,&mensagem,sizeof(mensagem),0);
					 
					    if (bytesenviados == -1)
					    {
					        printf("Falha ao executar send()");
					        exit(EXIT_FAILURE);
					    }
						close(socketId);
					}
					break;
				case 2:
					sem->P();
					c.saveCursor();
					c.moveCursor(10,4);
					trem = (trem+1)%8;
					if(trem == 0)
						cout<<"TODOS"<<endl;
					else
						cout<<trem<<"    "<<endl;
					c.resumeCursor();
					fflush(stdout);
					sem->V();
					break;
				case 3:
					if(!connected){
						sem->P();
						c.saveCursor();
						c.moveCursor(12,2);
					    connected = true;
						cout<<"   Conectado"<<endl;
						c.resumeCursor();
						fflush(stdout);
						sem->V();
					}
					else {
						sem->P();
						c.saveCursor();
						c.moveCursor(12,2);
					    connected = false;
						cout<<"Desconectado"<<endl;
						c.resumeCursor();
						fflush(stdout);
						sem->V();
					}

					break;
				default:
					break;
			}
			this_thread::sleep_for(chrono::milliseconds(250));
		}
		this_thread::sleep_for(chrono::milliseconds(17));
	}
}

void potControl(int* vel)
{
	Cursor c;

	int lastVel = -1, valuePot; // vai rodar a primeira vez;

	while(1)
	{
		valuePot = readAnalog(1); 
		if(valuePot < 300)
			*vel = 10;
		else if (valuePot < 600)
			*vel = 20;
		else if (valuePot < 900)
			*vel = 30;
		else if (valuePot < 1200)
			*vel = 40;
		else if (valuePot < 1500)
			*vel = 50;
		else if (valuePot < 1800)
			*vel = 60;
		else if (valuePot < 2100)
			*vel = 70;
		else if (valuePot < 2400)
			*vel = 80;
		else if (valuePot < 2700)
			*vel = 90;
		else if (valuePot < 3000)
			*vel = 100;
		else if (valuePot < 3300)
			*vel = 110;
		else if (valuePot < 3600)
			*vel = 120;
		else if (valuePot < 3900)
			*vel = 130;
		else if (valuePot < 4200)
			*vel = 140;
		else if (valuePot < 4500)
			*vel = 150;
		else if (valuePot < 4800)
			*vel = 160;
		else if (valuePot < 5100)
			*vel = 170;
		else if (valuePot < 5400)
			*vel = 180;
		else if (valuePot < 6700)
			*vel = 190;
		else
			*vel = 200;

		if (lastVel != *vel)
		{
			lastVel = *vel;

			sem->P();
			c.saveCursor();
			c.moveCursor(9,5);
			cout<<200 - *vel<< " " << endl;
			c.resumeCursor();
			fflush(stdout);
			sem->V();
		}

		this_thread::sleep_for(chrono::milliseconds(250));
	}
}

void signalHandlerFunction (int sig)
{
	delete sem;

	system("stty icanon echo");
	system("clear");
	fflush(stdout);
	kill(getpid(), SIGKILL);
}

