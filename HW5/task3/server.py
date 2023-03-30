import time
from datetime import datetime
import socket

port = 8080
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
s.settimeout(1)
s.bind(("", port))

while True:
    s.sendto(datetime.now().strftime("%H:%M:%S").encode("utf-8"), ("<broadcast>", port))
    time.sleep(1)