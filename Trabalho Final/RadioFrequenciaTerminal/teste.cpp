#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctacs/ct_api.h>
#include <map>

using namespace std;

#define CT          1
#define HOST        2
#define REMOTE_HOST 5

#define ICC1        0

using namespace std;

// CT-BCS - Cardterminal Basic Command Set
const unsigned char RESET_CT[] = {0x20, 0x11, 0x00, 0x00, 0x00};  
const unsigned char REQ_ICC[] = {0x20, 0x12, 0x01, 0x00, 0x01, 0x0a};  
const unsigned char EJECT_ICC[] = {0x20, 0x15, 0x01, 0x03, 0x01, 0x0a};

// Página 13 da API do ACR1222L (Get Data)
const unsigned char GET_ICCUID[] = {0xff, 0xca, 0x00, 0x00, 0x00};


/*	// Imprime a resposta em hexadecimal (Debug)
	void xdata (unsigned char *addr, int count)
	{  
		int i, j;  
			
		if (count > 0)  
		{  
			for (j = 0 ; j<=(count /16); j++)  
			{  
				printf(" %.2x: ", j*16);  
				for (i=0; i<16 ; i++)  
				{  
					if (j*16+i>=count)  
						printf("   ");  
					else  
						printf(" %.2x",addr[j*16+i]);  
				}  
			}  
			printf("\n");  
		}  
		
	} */


string getUserByTag(string tag, int count) {
	string line;
	ifstream myfile ("tag_users.txt");
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
		 	if(line.compare(0, count, tag) == 0){
		 		return line.substr((count)+1);
		 	}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	return "";
}

void insertUserByTag(string tag, string idDiscente) {
	string line = "";
	string file = "";
	ifstream myfile2 ("tag_users.txt");
	if (myfile2.is_open()) {
		while (getline (myfile2,line)) {
			file += line + '\n';
		}
		myfile2.close();
	}
	ofstream myfile("tag_users.txt", ios::app);
	tag += " hugopdf\n";
	file += tag;
	myfile << tag;
	myfile.close();
}

string getUser (unsigned char *addr, int count) {  	
	stringstream tag;

	//out << endl << "Tag UID[" << count-2 << "]: ";

	for (int i = 0 ; i < count-2; i++) {
		//printf("%.2x",addr[i]);
		if (addr[i] < 0x10)
			tag << "0" << hex << (int)addr[i];
		else
			tag << hex << (int)addr[i];
	}
	//cout << endl << endl;
	return getUserByTag(tag.str(),(2*(count-2)));
}

void insertDiscentePresente(int idDiscente) {
	string line = "";
	string file = "";
	string tag = to_string(idDiscente) + '\n';
	ifstream myfile2 ("presentes.txt");
	if (myfile2.is_open()) {
		while (getline (myfile2,line)) {
			file += line + '\n';
		}
		myfile2.close();
	}
	ofstream myfile("presentes.txt", ios::app);
	file += tag;
	myfile << tag;
	myfile.close();
}

void createListDiscenteTurma(string idTurma, string login, string password) {
	string comando = "python create_list_discente_turma.py " + login + " " + password + " " + idTurma ;
	system(comando.c_str());
	fflush(stdout);
}

map<int, string> getDiscentesTurma() {
	string line = "", file = "", nomeDiscente = "";
	int idDiscente = 0;
	map<int,string> turmas;
	ifstream myfile2 ("nome_id_discente.txt");
	if (myfile2.is_open()) {
		while (getline (myfile2,line)) {
			nomeDiscente = line;
			getline (myfile2,line);
			idDiscente = atoi(line.c_str());
			turmas.insert(pair<int,string>(idDiscente,nomeDiscente));
		}
		myfile2.close();
	}
	return turmas;
}

map<int, string> getTurmasDocente() {
	string line = "", file = "", nomeTurma = "";
	int idTurma = 0;
	map<int,string> turmas;
	ifstream myfile2 ("turmas_docente.txt");
	if (myfile2.is_open()) {
		while (getline (myfile2,line)) {
			nomeTurma = line;
			getline (myfile2,line);
			idTurma = atoi(line.c_str());
			turmas.insert(pair<int,string>(idTurma,nomeTurma));
		}
		myfile2.close();
	}
	return turmas;
}

string readCard(){
	char retval;
	unsigned short ctn;
	unsigned short pn;
	unsigned char sad;
	unsigned char dad;

	// REQUEST ICC
	unsigned char command[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned short lenc = sizeof(command);
	unsigned char response[300];
	unsigned short lenr = sizeof(response);
	unsigned short i;
	ctn = 1;
	pn = 1;
	string login = "";

	// Initialize card terminal
	retval = CT_init(ctn, pn);
	if (retval != OK)
	{
		cout << "Error: CT_init failed with error " << retval << endl;
		exit (-1);
	}
	
	memcpy(command, RESET_CT, sizeof(RESET_CT));  
	sad = HOST;  
	dad = CT;  
	lenr = 200;  
	lenc = sizeof(RESET_CT);  
	 
	retval =CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
	if (retval != OK)  
	{  
		cout << "RESET_CT not successful" << endl;
		exit (-1);
	}

	cout << "Apresente o cartão..." << endl;
	
	do
	{
		memcpy(command, REQ_ICC, sizeof(REQ_ICC));  
		sad = HOST;  
		dad = CT;  
		lenr = 200;  
		lenc = sizeof(REQ_ICC);  

		retval =CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
		if (retval != OK)  
		{  
			cout << "REQ_ICC not successful" << endl;  
			exit (-1);  
		}

	} while (response[0] != 0x90); 

	// Pega o UID do ICC do Byte menos significante para o mais 
	memcpy(command, GET_ICCUID, sizeof(GET_ICCUID));  
	sad = HOST;  
	dad = ICC1;
	lenr = 200;  
	lenc = sizeof(GET_ICCUID);  

	retval = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
	if (retval != OK)  
	{  
		cout << "GET_ICCUID not successful" << endl;  
		exit (-1);  
	}
	login = getUser(response, lenr);
	//cout << login << endl;

	// Close card terminal
	retval = CT_close(ctn);
	if (retval != OK)
		cout <<"Error: CT_close failed with error " << retval << endl;
	return login;
}

int main(int argc, char *argv[]){
	FILE *fp;
	char path[1035];
	char *turma;

	string username, password;
	cout << "Digite seu login: ";
	cin >> username;
	cout << "Digite sua senha: ";
	cin >> password;
	string comando = "python get_turma.py " + username + " " + password;
	fp = popen(comando.c_str(), "r");

	//Verifica se o comando foi executado
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}
	else{
		fgets(path, 1034, fp);
		pclose(fp);
		string turma(path);
		turma = turma.substr(0,strlen(path)-1);
		if(turma != "[]"){
			cout << "Selecionando turmas do docente" << endl;
			map<int, string> turmas = getTurmasDocente();
			cout << "Selecionando turma para lançar frequencia" << endl;
			turma = to_string(turmas.begin()->first);
			cout << "Selecionando discentes da turma" << endl;
			createListDiscenteTurma(turma, username, password);
			cout << "Turma aberta para registro de frequencia do discente" << endl;
			string idDiscente = readCard();
			string login = "ivanovitchm";
			while(idDiscente != login){
				map<int, string> discentes = getDiscentesTurma();
				insertDiscentePresente(atoi(idDiscente.c_str()));
				cout << "Aluno (" + discentes[atoi(idDiscente.c_str())] + ") presente" << endl;
				idDiscente = readCard();
			}
			comando = "python insert_frequencia.py " + login;
			system(comando.c_str());
			fflush(stdout);
			cout << "Frequencias Lançadas" << endl;
		}
		else
			cout << "O login (" << username << ") não pertence a um docente" << endl;
	}

	return 0;
}
