import socket
from time import sleep
import win32api
import win32con

#PATH = "C:\\Users\\ethan\\OneDrive\\Documents"
BUFF_SIZE = 2024
info = ('localhost', 12345)
print("Starting!")
serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

serv.bind(info)

serv.listen(1)
try:
    while True:
        client_sock, client_addr = serv.accept()
        client_sock.sendall("Connected".encode())
        print(client_addr, "connected")

        fileName = client_sock.recv(1024).decode()
        client_sock.sendall("Complete".encode())
        # Opens message box with message specified in second part of split message received
        win32api.MessageBox(None, fileName.split(":")[1], "Error", win32con.MB_OK | win32con.MB_ICONEXCLAMATION)


finally:
    serv.close()

