#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>

using namespace std;

bool isPai(long ppid, long pid) {
    char path[40], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%ld/status", pid);

    statusf = fopen(path, "r");
    if(!statusf)
        return false;

    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "PPid:", 5) != 0)
            continue;
        
        p = line + 5;
        while(isspace(*p)) ++p;

        break;
    }

    fclose(statusf);

    if(ppid == atoi(p))
        return true;
    else
        return false;
}

bool isValid(long pid) {
    char path[40], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%ld/status", pid);

    statusf = fopen(path, "r");
    if(!statusf)
        return false;

    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "Pid:", 4) != 0)
            continue;
        
        p = line + 4;
        while(isspace(*p)) ++p;

        break;
    }

    fclose(statusf);

    if(pid == atoi(p))
        return true;
    else
        return false;
}

list<int> getProcessosAbertos(){
    FILE *fp;
    char path[1035];
    list<int> processosAbertos;

    string comando = "ls /proc | grep '^[0-9]'";

    fp = popen(comando.c_str(), "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        processosAbertos.push_back(atoi(path));
    }

    /* close */
    pclose(fp);

    return processosAbertos;
}

string getArvore(long pid){

    string json = "{ pid: " + to_string(pid) + ", filhos: [";

    list<int> processosAbertos = getProcessosAbertos();

    for(list<int>::iterator it = processosAbertos.begin(); it != processosAbertos.end(); ++it){
        if(isPai(pid,*it)){
            if (json.back() != '[')
                json += ",";
            json += getArvore(*it);
        }
    }
    json += " ] }";

    return json;
}