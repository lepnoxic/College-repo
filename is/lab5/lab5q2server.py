import socket, threading
import hashlib
from time import sleep
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 8000))
server.listen()
client, address = server.accept()

print("Connected")

def send():
    while(True):
        payload = input()
        if ('corrput' in payload):
            client.send((payload + 'corrputed').encode())
        else:
            client.send(payload.encode())
        hash_local = hashlib.sha256(payload.encode()).hexdigest()
        
        # Receive the hash from the server
        hash_server = client.recv(1024).decode().strip()
        
        print(hash_local)
        print(hash_server)

        if hash_local != hash_server:
            print("Corruption Detected")
        else:
            print("No corruption during communication")

def recieve():
    while(True):
        output = client.recv(1024).decode()
        
        hash_server = hashlib.sha256(output.encode()).hexdigest()
        
        client.send(hash_server.encode())


recv_thread = threading.Thread(target=recieve)
send_thread = threading.Thread(target=send)

recv_thread.start()
send_thread.start()