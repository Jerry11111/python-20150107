#coding=utf-8
# 别惊讶，整个程序确实只用了两行代码
import urllib.request
import urllib.parse
import re
import os
import imp
import sys
import string
print (sys.getdefaultencoding())
#imp.reload(sys)
def down_http_pic(url, root_path):
	op = urllib.request.urlopen(url)
	#content = op.read().decode('utf-8')
	content = op.read().decode()
	code = op.getcode()
	info = op.info()
	#print 'code: %d\ninfo: %s\ncontent: %s'%(code, info, content)
	p = re.compile('<img[^>]*src[=\'\"\s]+([^\"\']*)[\"\']?[^>]*>', re.I)
	r = p.findall(content)
	print (r)
	for ele in r:
		pic_name = os.path.basename(ele)
		if not ele.startswith('http'):
			ele = 'http:' + ele 
		ele = urllib.parse.quote(ele, safe=string.printable) 
		print (ele)
		path = root_path + pic_name
		urllib.request.urlretrieve(ele, path)
url = 'http://www.baidu.com'
url = 'http://www.csdn.net/'
root_path ='/home/xiayiguo/github/python-20150107/http_down_pic/' 
down_http_pic(url, root_path)
