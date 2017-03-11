# Trabalho 1.1 - Manipulação de Processos

###Parte 1: Fork Bomb

####Objetivo
Implementar na BeagleBone um programa que evite o fork bomb.

####Requisitos:
* Evitar o travamento ao executar while(1) fork();
* Capturar mensagens de exceção geradas.
* Configurar parâmetro correspondente ao nº de processos suportados pelo programa.

###Parte 2: Hierarquia de Processos

####Objetivo
Implementar um programa que através de um processamento na pasta /proc imprima informações sobre os processos.

####Requisitos:
* Dado o ID de um processo (PID) imprimir a árvore de hierarquia (filhos, netos, bisnetos, tataranetos, etc.).
* A saída deve estar estruturada em algum formato conhecido (JSON, csv, etc) e de fácil manipulação.
* Imprimir a cada x instantes de tempo:
  * Número total de processos no sistema operacional
  * Número total de processos no sistema operacional organizados por usuário
  
###Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

###Disponível em: 
https://github.com/joelffg/ProjetoSO/tree/master/Trabalho%201.1

