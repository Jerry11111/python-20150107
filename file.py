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
<<<<<<< HEAD
=======
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
op()
>>>>>>> 82e222a433887da579971adf05516be19e26beb8
