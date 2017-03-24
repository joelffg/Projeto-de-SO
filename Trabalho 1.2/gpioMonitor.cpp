#include "MonitorarAPI.cpp"

using namespace std;

int main(int argc, char *argv[]){

	/* aqui faz todas as configurações para os gio de entrada e saída */
	long freeMem, maxMen;
	float percent;
	ifstream infoMem, infoPid;
	string aux;
	power light = off;

	while (true) {

		system("cat /proc/meminfo | head -2 | awk '{print $2}' > monitorAux.txt");
		infoMem.open("monitorAux.txt");

		if (infoMem.is_open()) {

			getline(infoMem, aux);
			maxMen = stoi(aux);

			getline(infoMem, aux);
			freeMem = stoi(aux);

			infoMem.close();
			system("rm monitorAux.txt");
		}
			else {
			cout << "Falha na leitura do arquivo de info de memória!" << endl;
			system("rm monitorAux.txt");
			exit(1); 
		}

		percent = (float)(maxMen - freeMem) *100 / maxMen;

		if(percent < 25.0f) {
			setVermelho(off);
			setAmarelo(off);
			setVerde(on);
		}
		else if (percent < 50.0f) {
			setVermelho(off);
			setAmarelo(on);
			setVerde(off);
		}
		else if (percent < 75.0f) {
			setVermelho(on);
			setAmarelo(off);
			setVerde(off);
		}
		else {
			if (buttonIsPressed()) {
				system("ps aux --sort=-%mem | head -2 | tail -1 | awk '{print $2}' > killAux.txt");
				infoPid.open("killAux.txt");

				if (infoPid.is_open()) {
					getline(infoPid, aux);
					infoPid.close();
					system("rm killAux.txt");

					string kill = "kill -9 ";
					kill += aux;

					system(kill.c_str());

					// apaga todos
					setVermelho(off);
					setAmarelo(off);
					setVerde(off);

					// 3,5s + 0,5 padrão				
					usleep(3500000);
				}
				else {
					cout << "Falha na leitura do arquivo de info do PID!" << endl;
					system("rm killAux.txt");
					exit(2);
				}
			}
			else {
				setAll(light);
			    usleep(500000);
				if(light == off)
					light =  on;
				else
					light = off;
			}
		}

		usleep(500000);
	}
	setAll(off);
}