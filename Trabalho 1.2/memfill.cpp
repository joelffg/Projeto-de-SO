#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <string.h>
#include <unistd.h>

using namespace std;

bool eatPercent(long total,int chunk){
	long i;
	for(i=0;i<total;i+=chunk){
		short *buffer= (short*)malloc(sizeof(char)*chunk);
		if(buffer==NULL){
			return false;
		}
		memset(buffer,0,chunk);
	}
	return true;
}

int main(int argc, char *argv[]){

	ifstream freeMem;
	string aux;
	int chunk=1024;
	long size = 0;

	system("cat /proc/meminfo | head -2 | tail -1 | awk '{print $2}' > fillAux.txt");
	freeMem.open("fillAux.txt");

	if (freeMem.is_open()) {
		getline(freeMem, aux);
		size = stoi(aux);
		size *= 1024;
		size /= 100; // porcento;

		freeMem.close();
		system("rm fillAux.txt");
	}
	else {
		cout << "Falha na leitura do arquivo de info de memória!" << endl;
		system("rm fillAux.txt");
		exit(1); 
	}

	for (int i = 0; i < 100; i++) {
		eatPercent(size,chunk);
		usleep(500000); // dorme 0,5s (logo, come 2 porcento por segundo)
	}

	printf("Done, press any key to free the memory\n");
	getchar();
}