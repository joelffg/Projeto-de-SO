# Trabalho 1.3 - Threads, ADC e GPIO

### Objetivo
Implementar um controle de video game (joystick) usando a BeagleBoneBlack e as ferramentas do sistema operacional. 

### Requisitos:
1. Funcionalidade:
* Utilizar para teste qualquer jogo disponibilizado de forma open source.
* É possível achar códigos de jogos de terminal no GitHub (Ex.: Tetris, Ping-Pong, Naves, etc).
* Também é possível implementar protótipo de jogos simples.
2. Controle:
* 3 tipos de movimentos e usar potenciômetro (ADC), LDR (ADC) e botão (GPIO IN).
3. Threads:
* Coleta de informações do controle será feita por 3 threads c/ prioridades diferentes.
* Maior prioridade: thread do potenciômetro.
* Menor prioridade: thread do botão terá a menor prioridade.

### Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

### Disponível em: 
https://github.com/joelffg/ProjetoSO/tree/master/Trabalho%201.3