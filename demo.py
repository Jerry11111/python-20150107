#coding=utf-8
import datetime
def test_print():
	print("hello world!")
	print(None);
	print(1, 2, 3, "a", "b", "c")# 1 2 3 a b c
	# sepָ���ָ���Ĭ��Ϊ�ո�, endָ�����з�Ĭ��Ϊ\n
	print(1, 2, 3, "a", "b", "c", sep = ",", end = "")# 1,2,3,a,b,c
f = isinstance("str", str);# �ж϶����Ƿ��Ǻ������͵�ʵ��
print(f)
str1 = "abc";
s = str1.encode();
print(s)
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
test_time()
