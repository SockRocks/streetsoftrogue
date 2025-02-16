import socket
from os.path import exists
from time import sleep
PORT = 49152
servInfo = ("localhost", 12345)
BUFF_SIZE = 8024
fileName = input("File Name>>")
if fileName == "no":
    message = input("Message to Send>>")
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(servInfo)
    client.sendall(f"m:{message}".encode())
    status = client.recv(1024).decode()
    while status != "Complete":
        pass
    client.close()
    exit()
path = input("path>>")
if not exists(path):
    raise FileNotFoundError
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(servInfo)

status = client.recv(1024).decode()
if status == "Connected":
    print(status)
    client.sendall(fileName.encode())
    status = client.recv(1024).decode()
    if status == "created":
        print("File", status)
        with open(path, 'rb')as reader:
            while chunk := reader.read(BUFF_SIZE):
                client.sendall(chunk)
                sleep(1)
        client.sendall(b'')
        client.sendall("complete".encode())
        print("Completed")
    else:
        print("error")
    client.close()