import socket
import sys

hostname = sys.argv[1]
port = int(sys.argv[2])
filename = sys.argv[3]

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((hostname, port))
client_socket.send(f"GET /{filename} HTTP/1.1".encode('utf-8')) 

while True:
	data = client_socket.recv(1024)

	if not data:
		break

	print(data.decode())