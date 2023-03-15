import socket
import os
import threading
import queue
import sys

active = 0
q = queue.Queue()
lock = threading.Lock()

def handle_client(conn, addr):
    file_path = conn.recv(1024).split()[1].decode()
        
    if os.path.isfile(file_path):
        file = open(file_path, "rb")
        data = file.read()

        conn.sendall(f'HTTP/1.1 200 OK\r\nContent-length: {os.path.getsize(file_path)}\r\nContent-Type: text/html\r\n\r\n'.encode('utf-8'))
        conn.sendall(data)
        
        file.close()
    else:
        conn.sendall(b'HTTP/1.1 404 Not Found\r\nContent-Length: 0')

    conn.close()

    lock.acquire()
    
    global active
    active -= 1
    if not q.empty():
        active += 1
        threading.Thread(target=handle_client, args=q.get()).start()
    
    lock.release()


if __name__ == '__main__':
    port = 8080
    
    max_connections_count = int(sys.argv[1])

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('', port))

    server_socket.listen()
    while True:
        conn, addr = server_socket.accept()

        lock.acquire()
        
        if active == max_connections_count:
            q.put((conn, addr))
        else:
            active += 1
            threading.Thread(target=handle_client, args=(conn, addr)).start()
        
        lock.release()