import socket
import sys

host, min_port, max_port = sys.argv[1], int(sys.argv[2]), int(sys.argv[3])

print("Free ports:")

while min_port < max_port:
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind((host, min_port))
        sock.close()
        print(min_port)
        min_port += 1
    except:
        min_port += 1