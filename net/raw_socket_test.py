#import socket
#print('hello world!')
#s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_IP)
#s.bind(("lo", 8080))
#s.listen(1)
#conn, addr = s.accept()
#with conn:
#	print('Connected by', addr)
#	data = conn.recv(1024)
#	print('Received', repr(data))
import socket
port=8081
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
#从指定的端口，从任何发送者，接收UDP数据
s.bind(('',port))
print('正在等待接入...')
while True:
    #接收一个数据
    data,addr=s.recvfrom(1024)
    print('Received:',data,'from',addr)
