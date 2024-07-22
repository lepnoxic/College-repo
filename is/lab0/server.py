import socket, threading
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 8000))
server.listen()
client, address = server.accept()

print("Connected")

def send():
	while(True):
		payload = input()
		client.send(payload.encode())

def recieve():
	while(True):
		output = client.recv(1024).decode()
		print(output)

recv_thread = threading.Thread(target=recieve)
send_thread = threading.Thread(target=send)

recv_thread.start()
send_thread.start()
