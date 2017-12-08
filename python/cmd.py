#!/usr/bin/python
# -*- coding: UTF-8 -*-
import os    
import re

def confir(str):
    for i in range(0,32):
        str = str.replace(chr(i),'')
    return  str 

def test_system():
    os.system("ls") # 不能获取返回消息

def test_popen():
    c = 'top -n 1 | tee mm-statck-top.log'
    print (c)
    fp = os.popen(c)# 获取返回
    line = fp.readline()    
    while line:    
      line = fp.readline()   
      line = line.strip()    
      #print line.find('tomcat')  
      if line.find('java') != -1: 
        print (line)    
    for line in fp.readlines():
      line = line.strip()    
      if line.find('java') != -1:  
        print (line)
        print (line.split())
        w = line.split()[1].strip()
        pid = int(w)
        c = 'top -H -p %d -n 1> ~/mm-stack-top-%d.log'%(pid, pid)
        os.system(c)
        print (c)
        c = 'sudo kill -3 %d'%(pid)
        os.system(c)
        print (c)
        c = 'tail -n 2000 /var/log/tomcat7/catalina.out > ~/mm-stack-%d.log'%(pid)
        os.system(c)
        print (c)
test_system()
