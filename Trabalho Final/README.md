# Trabalho Final

### Antes de usar
1. Login como root.
```
$ sudo su
```

2. Entre na pasta "ctacs_linux_bin-1.0.1" e execute
```
# ./install.sh
```

#### Para compilar use:
```
$ g++ teste.cpp -o teste -lctacs
```

#### Para usar:
```
$ ./teste
```

#### Exemplo de saída:
1. Sem o cartão
```
RESET_CT:
 00:  90 00                                             [�               ]

GET_STAT46:
 00:  46 0f 48 4b 41 43 53 20 20 41 43 52 31 2e 30 2e   [F HKACS  ACR1.0.]
 10:  31 90 00                                          [1�              ]

GET_STAT80
 00:  80 01 02 90 00                                    [�  �            ]

Please insert Card into Slot #1 within 5sec.
REQ_ICC:
 00:  62 00                                             [b               ]

SELECT MF
SELECT_MF not successful
```

2. Com o cartão
```
RESET_CT:
 00:  90 00                                             [�               ]

GET_STAT46:
 00:  46 0f 48 4b 41 43 53 20 20 41 43 52 31 2e 30 2e   [F HKACS  ACR1.0.]
 10:  31 90 00                                          [1�              ]

GET_STAT80
 00:  80 01 05 90 00                                    [�  �            ]

Please insert Card into Slot #1 within 5sec.
REQ_ICC:
 00:  62 01                                             [b               ]

SELECT MF
 00:  63 00                                             [c               ]

SELECT GDO
 00:  63 00                                             [c               ]

READ BINARY
 00:  63 00                                             [c               ]
```

### Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

### Disponível em: 
https://github.com/joelffg/ProjetoSO/tree/master/Trabalho Final
