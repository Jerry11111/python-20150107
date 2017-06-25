import os

def del_svn(path):
	files = os.listdir(path)
	for f in files:
		print(f)
path = '/home/xiayiguo'
del_svn(path)
