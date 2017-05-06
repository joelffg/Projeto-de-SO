from time import sleep
import os
import random
import sys
import socket
import time

from copy import deepcopy

from socket import error as SocketError
import errno

def readAnalog(number):
	PATH_ADC= "/sys/bus/iio/devices/iio:device0/in_voltage" + str(number) + "_raw"
	fs= open(PATH_ADC, "r")
	ret= int(fs.readline())
	fs.close()
	return ret

def controlPot ():
	number = readAnalog (1)
	return number

def controlLDR():
	number = readAnalog(0)
	return number

def controlButton():
	export=open("/sys/class/gpio/export","a")
	export.write("115")
	valueFile=open("/sys/class/gpio/gpio115/value","r")
	value=int(valueFile.readline())
	valueFile.close()
	try:
		export.close()
	except: 
		pass
	return value

def run():
	HOST = '192.168.7.1'     # Endereco IP do Servidor
	PORT = 4325            # Porta que o Servidor esta
	udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	dest = (HOST, PORT)
	#tcp.connect(dest)
	print 'Para sair use CTRL+X\n'
	msg = ""
	while msg <> '\x18':
		msg = str(controlPot()) + "," + str(controlButton()) + "," + str(controlLDR())
		udp.sendto (msg, dest)
		print(msg)
		time.sleep(0.1)
	tcp.close()

run()