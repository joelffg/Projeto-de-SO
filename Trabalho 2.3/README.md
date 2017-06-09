# Trabalho 2.3 - Gerência de Memória

### Objetivo:
Implementar uma solução para sincronização de trens urbanos.
A solução deve utilizar as seguintes ferramentas:
* Semáforos
* Thread
* Socket
* Sinais/Slots
* Gui (Qt)
* BeagleBoneBlack (GPIO)
* Problema de concorrência

### Requisitos:
1. Servidor:
* Trens (uma thread por trem)
* Todos os trens se movem no sentido horário
* Separar a lógica do Front-End e do Back-end.
* Servidor deve ser executado no PC e conter uma interface gráfica de acompanhamento dos trens semelhante ao apresentado anteriormente.
* Os trens inicializam parados e #dica fora de regiões críticas
* Implementar um socket para comunicação com o cliente (controlador dos trens)
* Uma thread separada irá tratar as requisições do cliente
* A sincronização dos trens deverá utilizar semáforos binários
* A lógica de implementação do "Placar de Semaforos", "Log de eventos" e "Tempo de Viagem" é livre para os grupos
* Ausência de deadlock e colisões entre os trens são um dos principais requisitos da solução

2. Cliente:
* Deverá ser implementado na BeagleBoneBlack
* As seguintes funcionalidades devem ser utilizadas:
	* Conectar/desconectar do servidor
	* Ligar/Desligar todos os trens
	* Ligar/Desligar um trem específico
	* Aumentar a velocidade de um trem específico
* A interface com o usuário será realizada por:
	* 3 botões (up, down e play)
		* Os botões up e down serão utilizados para selecionar uma das funcionalidades suportadas enquanto que botão play irá executar a funcionalidade selecionada
	* Potenciometro (controlar a velocidade)
	* A interface (terminal) para seleção das funcionalidades é de livre escolha
* A comunicação com o servidor será realizada através de um socket

#### Para compilar use:

Para compilar o Servidor use o Qt Creator e dê um "Build Project"

Para compilar o Cliente use:
```
$ make
```

#### Para usar:

Para usar o Servidor use o Qt Creator e dê um "Play"

Para usar o Cliente, execute como super user:
```
$ ./clienteTrens
```

### Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

### Disponível em: 
https://github.com/joelffg/ProjetoSO/tree/master/Trabalho%202.3
