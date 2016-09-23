#coding=UTF-8
import os,sys
#取出当前工作目录里的文件名列表。
filenames=os.listdir(os.getcwd())
print (type(filenames))
print (filenames)
for f in filenames:
    print (f, type(f))
def file_op():
    url = 'http://www.baiu.com/a/b/c.gif'
    url = 'http://i.imgur.com/ZaTRsYLb.jpg'
    name = os.path.basename(url)
    print (name)
#file_op()
