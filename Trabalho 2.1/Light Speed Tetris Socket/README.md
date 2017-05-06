# Light Speed Tetris Socket:video_game: :rocket: :zap: :flashlight: :video_game:
![](https://github.com/joelffg/ProjetoSO/blob/master/Trabalho%201.3/Light%20Speed%20Tetris%20Socket/img/tetris.png?raw=true)

### Descrição
Tetris (baseado em [Tetris](https://github.com/fanux/tetris)) jogado na [BeagleBoneBlack](https://beagleboard.org/black), utilizando-se de alguns componentes eletrônicos como sendo os controladores do jogo:
* Potenciômetro: Mover peça para a direita ou esquerda
* Fotoresistor (Light-Dependent Resistor - LDR): Velocidade da queda das peças
* Pushbutton Switch: Rotaciona a peça

Utilizando 2 programas para fazer o jogo funcionar:
* O primeiro programa é o Servidor que executa o jogo
* O segundo programa é o Cliente que captura os controles do jogo e os envia para o Servidor

#### Para compilar use:

Para compilar o Servidor use
```
$ make
```

#### Para usar:
Para usar o Servidor, execute como super user:
```
$ ./game
```
Para usar o Cliente, execute como super user:
```
$ python cliente.py
```

### Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

### Disponível em: 
https://github.com/joelffg/ProjetoSO/blob/master/Trabalho%201.3/Light%20Speed%20Tetris%20Socket/