import socket  
import time  
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
sock.connect(('localhost', 8001))  
# time.sleep(2)  
sock.send('1'.encode())  
ret = sock.recv(1024).decode()
print(ret)  
sock.close()	
