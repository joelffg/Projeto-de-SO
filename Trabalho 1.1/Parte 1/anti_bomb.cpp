#include <iostream>
#include <unistd.h>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {

    map<string, int> procCount;
    map<string, string> pidMap;

    ifstream procList;
    ifstream straceLog;

    int clonLimit = 0;

    while (clonLimit < 50)
    {
        cout << "Digite um limite de clones para um processo (>=50): ";
        cin >> clonLimit;
    }

    while(1) {

        system("ps -ec | awk '{print $1,$6 }' > temp.txt");

        procList.open("temp.txt");

        if (procList.is_open()) {

            string word, pid;


            // Pula o cabeçalho (CMD e PID)
            for (int i = 0; i < 2; i++)
                procList >> pid;


            // Lê o arquivo e armazena das informações em mapas
            while(procList >> pid) {

                procList >> word;
                
                ++procCount[word];
                pidMap[pid] = word;
            }

            procList.close();
            

            // Faz uma varredura para encontrar algum nome com muitos processos associados
            for (map<string, int>::iterator it = procCount.begin(); it != procCount.end(); ++it) {
                
                if(it->second > clonLimit) {

                    bool starting = true;
                    int lowerPid, aux;

                    // Procura o processo pai
                    for (map<string, string>::iterator it2 = pidMap.begin(); it2 != pidMap.end(); ++it2) {
                        if (it->first.compare(it2->second) == 0) {

                            if (starting) {
                                lowerPid = stoi(it2->first);
                                starting = false;
                            }

                            else {
                                aux = stoi(it2->first);

                                if (lowerPid > aux) {
                                    lowerPid = aux;
                                }
                            }
                        }
                    }

                    // Roda um strace no processo suspeito
                    string straceCmd = "sudo timeout 0.5 strace -p ";
                    straceCmd += to_string(lowerPid);
                    straceCmd += " -o aux.txt";

                    system(straceCmd.c_str());

                    usleep(600000);

                    // Pega as 3 ultimas linhas do log do strace
                    straceLog.open("aux.txt");

                    if (straceLog.is_open()) {

                        string line, line1, line2, line3;


                        while (getline (straceLog,line)){
                           line3 = line2;
                           line2 = line1;
                           line1 = line;
                        } 

                        straceLog.close();

                        cout << line3 << endl;
                        cout << line2 << endl;
                        cout << line1 << endl;

                        // comando para matar a arvore com o número do gpid
                        string killCmd = "kill -9 -$(ps -o pgid= ";
                        killCmd += to_string(lowerPid);
                        killCmd += " | grep -o '[0-9]*')";

                        system(killCmd.c_str());
                    }
                    else {
                        cout << "Erro fatal na aplicação! Fechando...";
                        exit(-1);
                    }
                }
            }

            procCount.clear();
            pidMap.clear();
        }
        
        else {
            cout << "Erro fatal na aplicação! Fechando...";
            exit(-1);
        }

        usleep(10000000);
    }

    return 0; 
}