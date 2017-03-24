# Trabalho 1.2 - Tratamento de Sinais e GPIO

###Objetivo
Monitoramento (e finalização) de processos fazendo uso de GPIO na BeagleBoneBoard.

###Requisitos:
* Executar programa que em execução (processo) consuma de forma crescente um determinado recurso (CPU, memória, etc.);
* Usar GPIOs da BeagleBoneBoard para sinalizar, através de LEDs, o 
percentual de uso desse(s) recurso(s):
	1. LED verde acende se até 25% do recurso estiver sendo usado;
	2. LED amarelo acende se o uso do recurso estiver entre 25% e 50%;
	3. LED vermelho acende se o uso do recurso estiver entre 50% e 75%;
	4. Acima de 75% todos os LEDs ficarão piscando.
* Quando o recurso tiver ultrapassado os 75% um "botão do pânico" deve ser acionado e o processo que estiver causando o aumento do uso do recurso deverá ser terminado.
* Ao ser acionado o botão do pânico todos os LEDs ficarão apagados por "X" segundos e depois segue a lógica citada.
  
####Para compilar use:
g++ -std=c++11 gpioMonitor.cpp -o gpioMonitor

g++ -std=c++11 memfill.cpp -o memfill

####Para usar:
Executar como super user

./gpioMonitor

Em outra janela do bash:

./memfill

###Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

###Disponível em: 
https://github.com/joelffg/ProjetoSO/tree/master/Trabalho%201.2

