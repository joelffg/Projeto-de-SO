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

void saveFile(string input, int pid){
	string path = to_string(pid) + ".txt";
    ofstream out(path.c_str());
    out << input;
    out.close();
    printf("Arquivo %s gerado com sucesso\n", path.c_str());
}

int main(int argc, char *argv[])
{
	fd_set readfds;
	int    num_readable;
	struct timeval tv;
	int    num_bytes;
	char   buf[MAXBYTES];
	int    fd_stdin;

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	while(1) {

		fd_stdin = fileno(stdin);

		FD_ZERO(&readfds);
		FD_SET(fileno(stdin), &readfds);
		
		printf("Digite o PID desejado: ");
		fflush(stdout);
		num_readable = select(fd_stdin + 1, &readfds, NULL, NULL, &tv);
		if (num_readable == -1) {
			fprintf(stderr, "\nError in select : %s\n", strerror(errno));
			exit(1);
		}
		if (num_readable == 0) {
			system("clear");
			printf("Quantidade de processos ativos: ");
			fflush(stdout);
			system("ps aux | wc -l");
			printf("\n");
			printf("Quantidade de processos ativos por usuário:\n");
			fflush(stdout);
			system("ps -eo user=|sort|uniq -c");
			printf("\n");

			tv.tv_sec += 10;
			
		} else {
			num_bytes = read(fd_stdin, buf, MAXBYTES);

			if (num_bytes < 0) {
				fprintf(stderr, "\nError on read : %s\n", strerror(errno));
				exit(1);
			}

			if(isValid(atoi(buf)))
				saveFile(getArvore(atoi(buf)), atoi(buf));
			else
				printf("O pid:%d é inválido\n", atoi(buf));

		}
	}

	return 0;
}