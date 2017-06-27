import os
import sys

def del_svn(path):
	files = os.listdir(path)
	for name in files:
		f = os.path.join(path, name)
		if(name == '.svn'):
			del_file(f)
		else:
			if(os.path.isdir(f)):
				del_svn(f)
def del_file(path):
	if(os.path.isfile(path)):
		print('rm file: ', path)
		os.remove(path)
		return
	elif(os.path.isdir(path)):
		files = os.listdir(path)
		for f in files:
			f = os.path.join(path, f)
			del_file(f)
		print('rm dir: ', path)
		os.rmdir(path)
path = '/home/xiayiguo/test'
path = sys.argv[1]
del_svn(path)
#del_file(path)
# pass args
# o filename 1... args
#for i in range(0, len(sys.argv)):
	#print(i, sys.argv[i])
