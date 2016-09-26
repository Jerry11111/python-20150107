#coding=utf-8
import datetime
import urllib.request
def test_print():
	print("hello world!")
	print(None);
	print(1, 2, 3, "a", "b", "c")# 1 2 3 a b c
	# sep指定分隔符默认为空格, end指定换行符默认为\n
	print(1, 2, 3, "a", "b", "c", sep = ",", end = "")# 1,2,3,a,b,c
def test_type():
	f = isinstance("str", str);# 判断对象是否是后面类型的实例
	print(f)
	str1 = "abc";#字符串
	bstr1 = b"abc";#字节
	bstr2 = str1.encode();# 字符串转化为字节
	print("%s %s %s | %s %s %s"%(str1, bstr1, bstr2, type(str1), type(bstr1), type(bstr2)))
#test_type()
def test_if():
	x = 1;
	if x == 1:
		print("x = 1");
	elif x == 2:	
		print("x = 2");
	else:
		print("x = 3");

	for x in ["spam", "eggs", "ham"]:
		print(x, end=' ')
	print(x)
def test_list():
	lt = [123, 'spam', 1.23]
	ltlen = len(lt)
	lt0 = lt[0]
	lt[1] = 'abc'
	lt.pop(2)#删除第二个元素
	lt.append('ab');
	print("%d %d %s"%(ltlen, lt0, lt))
	for x in lt:
		print(x, end = ' ')
def test_tuple():
	tp = (123, 'spam', 1.23)
	print(len(tp))
	print(tp[2])
	print(tp)
	for x in tp:
		print(x, end = ' ')
#test_tuple()
def test_dict():
	# 构造dict
	a = dict(one=1, two=2, three=3)
	b = b = {'one': 1, 'two': 2, 'three': 3}
	print("%s %s"%(a, b))
	a0 = a["one"]
	alen = len(a)
	a["one"] = 5
	del a["three"]
	print("%d %d %s"%(a0, alen, a))
def test_time():
	#计算今天的时间
	today = datetime.date.today()
	#计算昨天的时间  
	yesterday = today - datetime.timedelta(days = 1)
	#计算明天的时间 
	tomorrow = today + datetime.timedelta(days = 1)  
	#打印这三个时间
	print(yesterday, today, tomorrow)
def test_file():
    print ("hello world!")
    rfo = open('/home/xiayiguo/ip.txt', "r")
    # read
    line = rfo.readline()#读取一行
    print("line: " + line)
    ft = rfo.read()
    print("read: " + ft) 
    #nt = "hell world";
    #wfo = open('/home/xiayiguo/ip.txt', "w+")
    # write
    #wfo.write(nt)
    #print(open('/home/xiayiguo/ip.txt', "r").read())
def test_urllib_request():
	resp = urllib.request.urlopen("http://www.baidu.com")
	data = resp.read() #字节
	str1 = str(data, 'utf-8')
	status = resp.status
	reason = resp.reason
	print("%d %s %s %s %s"%(status, reason, type(resp), type(data), type(str1)))
test_urllib_request()
