import sys
import socket

port = int(sys.argv[1])

server = socket.socket(socket.AF_INET6, socket.SOCK_STREAM) 
server.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 1)

server.bind(("::1", port))    
server.listen()

while True:
    conn, addr = server.accept()
    message = conn.recv(1024).decode()
    
    conn.sendall(message.upper().encode())