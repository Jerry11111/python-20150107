#coding=UTF-8
import os,sys
#取出当前工作目录里的文件名列表。
filenames=os.listdir(os.getcwd())
print type(filenames)
print filenames
for f in filenames:
    print f, type(f)
