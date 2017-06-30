
### Aparelho utilizado

ACS1222L-D1 USB NFC Reader with LCD (goo.gl/mVZkY8)

### Instalação do driver

1. Logue como superuser. (sudo su)

2. Para compilar o driver são necessaŕios os seguintes pacotes:
	
-> pcsclite 1.8.3 ou superior
# apt-get install libpcsclite-dev

-> libusb 1.0.9 ou superior
# apt-get install libusb-1.0-0-dev

-> flex
# apt-get install flex

-> perl
# apt-get install perl

-> pkg-config
# apt-get install pkg-config

3. Na pasta com o arquivo compactador:

# tar -jxvf acsccid-x.y.z.tar.bz2
# cd acsccid-x.y.z

# ./configure
# make
# make install

### Para compilar:

$ g++ teste.cpp -o teste -lctacs

### Para usar:

$ ./teste

### Autores:
* Joel Felipe - joelfelipe07@gmail.com
* Hugo Oliveira - hugotholiveira@hotmail.com

### Referências:
* http://www.acs.com.hk/download-manual/2737/API-ACR1222L-1.03.pdf
* http://manpages.ubuntu.com/manpages/zesty/man3/towitoko-ctbcs.3.html

### Disponível em: 
https://github.com/joelffg/ProjetoSO/tree/master/Trabalho%20Final