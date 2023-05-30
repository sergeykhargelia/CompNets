import sys
import socket

host = sys.argv[1]
port = int(sys.argv[2])

client = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
client.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 1)

client.connect((host, port))

message = input("Enter your message, please.\n")
client.sendall(message.encode())

result = client.recv(1024).decode()
print("Result:", result)