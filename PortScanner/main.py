# This program implements a simple port scanner

import pyfiglet
import socket
import sys
from datetime import datetime

def create_socket():
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except  socket.error as err:
		print(f"Socket Error {err}")
		sys.exit()
	else:
		return sock
	finally:
		print("Socket Creation Complete")



def host_name_resolve(hostName):
	try:
		hostIPAddr = socket.gethostbyname(hostName)
	except socket.gaierror:
		print("Cannot resolve host name")
		sys.exit()
	else:
		return hostIPAddr

def menu():
	ascii_banner = pyfiglet.figlet_format("PORT SCANNER")
	print("-" * 50)
	print(ascii_banner)
	print("-" * 50)
	print(str(datetime.now()))
	print("-" * 50)

	host_name = input("Host Name:")

	return host_name



def main():
	port = 80
	hostName = menu()
	ipAddr = host_name_resolve(hostName)
	sock = create_socket()
	sock.connect((ipAddr, port))



main()
