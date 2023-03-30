import socket

from datetime import datetime
import socket

port = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
s.bind(("", port))

while True:
    time = s.recvfrom(1024)[0].decode()
    print("current time: ", time)