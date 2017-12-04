#coding=UTF-8
import os,sys
#取出当前工作目录里的文件名列表。
filenames=os.listdir(os.getcwd())
#print (type(filenames))
#print (filenames)
#for f in filenames:
    #print (f, type(f))
def file_op():
    url = 'http://www.baiu.com/a/b/c.gif'
    url = 'http://i.imgur.com/ZaTRsYLb.jpg'
    name = os.path.basename(url)
    print (name)
#file_op()
def op():
	print ("hello world!")
	rfo = open('/home/xiayiguo/ip.txt', "r")
	# read
	ft = rfo.read()
	print("read: " + ft)
	nt = "hell world";
	wfo = open('/home/xiayiguo/ip.txt', "w+")
	# write
	wfo.write(nt)
	print(open('/home/xiayiguo/ip.txt', "r").read())
def f_read():
	print("read");
	fd = open('/home/xiayiguo/ip.txt', "r")
	# read
	str_data = fd.read()
	fd.close()
	print(type(str_data))
	print(str_data)
def f_write():
	print("write");
	str_word = "hell world";
	fd = open('/home/xiayiguo/ip.txt', "w+") #r只读，w可写，a追加 
	# write
	fd.write(str_word)
	fd.close()
	print(open('/home/xiayiguo/ip.txt', "r").read())
def p_exec():
	os.system('ls -l')# 无返回结果
	print(os.popen('ls -l ').read())# 有返回结果
f_write()
