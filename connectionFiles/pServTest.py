import socket
from time import sleep
import win32api
import win32con

PATH = "C:\\Users\\ethan\\OneDrive\\Documents"
BUFF_SIZE = 2024
info = ('localhost', 12345)

serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

serv.bind(info)

serv.listen(1)
try:
    while True:
        client_sock, client_addr = serv.accept()
        client_sock.sendall("Connected".encode())
        print(client_addr, "connected")

        fileName = client_sock.recv(1024).decode()
        if fileName.split(":")[0] == "m":
            win32api.MessageBox(None, fileName.split(":")[1], "Error", win32con.MB_OK | win32con.MB_ICONEXCLAMATION)
        else:
            print("Creating file", fileName)


            with open(PATH + "\\" + fileName, 'wb')as writer:
                client_sock.sendall("created".encode())
                print("Created")
                while chunk := client_sock.recv(BUFF_SIZE):
                    if chunk == "complete".encode():
                        break
                    writer.write(chunk)
            sleep(3)
        print( "Process", client_sock.recv(1024).decode())


finally:
    serv.close()

