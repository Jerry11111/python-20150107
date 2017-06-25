import socket
host = 'localhost'
port = 8001
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((host, port))
sock.listen(5)
print('server start, listen %d' %(port))
while True:
	conn,addr = sock.accept()
	print('accept ', addr)
	try:
		conn.settimeout(5)
		buf = conn.recv(1024).decode()
		print('recv %s' %(buf));
		conn.send('welcome to server!'.encode())
	except socket.timeout:
		print('time out')
	conn.close()
