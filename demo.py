#coding=utf-8
import datetime
def test_print():
	print("hello world!")
	print(None);
	print(1, 2, 3, "a", "b", "c")# 1 2 3 a b c
	# sepָ���ָ���Ĭ��Ϊ�ո�, endָ�����з�Ĭ��Ϊ\n
	print(1, 2, 3, "a", "b", "c", sep = ",", end = "")# 1,2,3,a,b,c
def test_type():
	f = isinstance("str", str);# �ж϶����Ƿ��Ǻ������͵�ʵ��
	print(f)
	str1 = "abc";#�ַ���
	bstr1 = b"abc";#�ֽ�
	bstr2 = str1.encode();# �ַ���ת��Ϊ�ֽ�
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
	print(len(lt))
	lt.append('ab');
	print(lt[3])
	lt[3] = 'abc'
	#lt.pop(3)
	print(lt)
	for x in lt:
		print(x, end = ' ')
#test_list()
def test_tuple():
	tp = (123, 'spam', 1.23)
	print(len(tp))
	print(tp[2])
	print(tp)
	for x in tp:
		print(x, end = ' ')
#test_tuple()
def test_time():
	#��������ʱ��
	today = datetime.date.today()
	#���������ʱ��  
	yesterday = today - datetime.timedelta(days = 1)
	#���������ʱ�� 
	tomorrow = today + datetime.timedelta(days = 1)  
	#��ӡ������ʱ��
	print(yesterday, today, tomorrow)
def test_file():
    print ("hello world!")
    rfo = open('/home/xiayiguo/ip.txt', "r")
    # read
    line = rfo.readline()#��ȡһ��
    print("line: " + line)
    ft = rfo.read()
    print("read: " + ft) 
    #nt = "hell world";
    #wfo = open('/home/xiayiguo/ip.txt', "w+")
    # write
    #wfo.write(nt)
    #print(open('/home/xiayiguo/ip.txt', "r").read())
test_file()
