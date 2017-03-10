#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fstream>
#include "arvore.cpp"

#define MAXBYTES 80

using namespace std;

//Salva o JSON em um arquivo nomeado como $pid.txt
void saveFile(string json, int pid){
	//Inicializa o nome do arquivo
	string path = to_string(pid) + ".txt";

	//Inicializa o arquivo
    ofstream out(path.c_str());

	//Envia o conteudo do json para o arquivo
    out << json;

    //Fecha o arquivo
    out.close();

    //Retorna uma mensagem de confirmação da geração do arquivo
    printf("Arquivo %s gerado com sucesso\n", path.c_str());
}

int main(int argc, char *argv[]) {

	//Inicialização das variáveis
	fd_set readfds;
	int    num_readable;
	struct timeval tv;
	int    num_bytes;
	char   buf[MAXBYTES];
	int    fd_stdin;

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	//Loop Principal do programa
	while(1) {

		//Zera as variáveis para o loop
		fd_stdin = fileno(stdin);
		FD_ZERO(&readfds);
		FD_SET(fileno(stdin), &readfds);
		
		printf("Digite o PID desejado (Digite -1 para parar): ");
		fflush(stdout);

		//Verifica se o usuário digitou algo
		num_readable = select(fd_stdin + 1, &readfds, NULL, NULL, &tv);

		//Mensagem de erro na verificação
		if (num_readable == -1) {
			fprintf(stderr, "\nError in select : %s\n", strerror(errno));
			exit(1);
		}

		//Se o usuário não digitou
		if (num_readable == 0) {
			system("clear");

			//Imprime a quantidade de processos ativos
			printf("Quantidade de processos ativos: ");
			fflush(stdout);
			system("ps aux | wc -l");
			printf("\n");

			//Imprime a quantidade de processos ativos por usuário
			printf("Quantidade de processos ativos por usuário:\n");
			fflush(stdout);
			system("ps -eo user=|sort|uniq -c");
			printf("\n");

			//Aumenta o tempo da verificação se o usuário digitou algo em 10 segundos
			tv.tv_sec += 10;
			
		//Se o usuário digitou
		} else {
			//Leitura da informação digitada pelo usuário
			num_bytes = read(fd_stdin, buf, MAXBYTES);

			//Mensagem de erro na leitura
			if (num_bytes < 0) {
				fprintf(stderr, "\nError on read : %s\n", strerror(errno));
				exit(1);
			}

			//Verifica se o usuário digitou -1 (Comando para sair do programa)
			if(atoi(buf) != -1)
				break;

			//Verifica se a informação digitada pelo usuário é um processo válido
			if(isValid(atoi(buf)))
				saveFile(getArvore(atoi(buf)), atoi(buf));
			else
				printf("O pid:%d é inválido\n", atoi(buf));

		}
	}

	return 0;
}