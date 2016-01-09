import time
import os
print 'Hello World!'
i = 1
time.sleep(1);
print type(i)
def run():
    #os.system('ping www.baidu.com')
    os.system('ls')
    print 'running'
#run()
def test_if():
	if i == 1:
		print 'ok'
	else:
		print 'error'
test_if()
