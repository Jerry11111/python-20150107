#-*- coding: utf-8 -*-
#coding=utf-8
import urllib.request
import json
from splinter.browser import Browser 
import time
def test():
	for i in range(0, 12):
		url = 'http://localhost:8080/gamebase-payserver/9/areapay?Y2lkPTEwMDAwMCZwPTIwMCZ1aT0xMDAxNzMzJmFjaWQ9c25vd2Zpc2gmYWM9c25vd2Zpc2gmYWlkPXs4NTY1OUU5OS0wNDU1NkVDMH0mcGM9MSZjbj3kuK3lm73np7vliqgmYXA9d2lmaSZjcmM9OTg4MDAwJmNybT0xMjA5MDAwJmN0PTE0Mjk2ODM0MDAxMDcmZGQ9RTcxdCZpbWVpPTEwMDg2Jmltc2k9NDYwMDA3ODgxODUwOTIyJm1hYz0wMDowODoyMjpkMDpiYjpmYiZtZnQ9U1VOSU5HJm1yPTQ3MjE3NiZwb3M9NC4yLjEmc2Q9MjQwJnN3PTQ4MCZzaD04NTQmbnc9V0lGSSZpYT1mZTgwOjo4OjIyZmY6ZmVkMDpiYmZiJXAycDAmbnM9bnVsbCZud249V0lGSSZzc2lkPSJUUC1MSU5LXzIuNEdIeiBGMiImcG9pbnQ9MSZjdj04'
		op = urllib.request.Request(url)
		resp = urllib.request.urlopen(op)
		print(i)
def test2():
	# 打印0 1 2 3 4
	for i in range(0, 5):
		print(i)
	# 打印0 2 4
	for i in range(0, 5, 2):
		print(i)
def test_json():
	obj = [[1,2,3],123,123.123,'abc',{'key1':(1,2,3),'key2':(4,5,6)}]
	encodedjson = json.dumps(obj)
	print(repr(obj))
	print(encodedjson)
	jstr = '''{
	"appid": "9013441301020150326103320124400",
	"consumecode": "160420527578",
	"cpid": "86009182",
	"fid": "22744",
	"hret": "0",
	"orderid": "000000000000000000007214",
	"ordertime": "20160912191825",
	"payfee": 1900,
	"paytype": "2",
	"signMsg": "24487fabc2694bf1f40f637300f091e6",
	"status": "00000"
	}'''
	print(jstr)
	o = json.loads(jstr)# json转化为dic
	print("%s %s"%(o, type(o)))
	str2 = json.dumps(o)# dic转化为json字符串
	print("%s %s"%(str2, type(str2)))
def test_req():
	jstr = '''{
	"appid": "9013441301020150326103320124400",
	"consumecode": "160420527578",
	"cpid": "86009182",
	"fid": "22744",
	"hret": "0",
	"orderid": "00000000000000000000xxxx",
	"ordertime": "20160912191825",
	"payfee": 1900,
	"paytype": "2",
	"signMsg": "24487fabc2694bf1f40f637300f091e6",
	"status": "00000"
	}'''
	o = json.loads(jstr)# json转化为dic
	orderid = o['orderid']
	start = 7515
	end = start + 6
	url = "http://localhost:8080/gamebase-payserver/sms/xiaowo/callback"
	for i in range(start, end):
		num = i
		print(num)
		o['orderid'] = orderid.replace('xxxx', "%d"%(num))
		#print(o['orderid'])
		op = urllib.request.Request(url)
		str1 = json.dumps(o)
		#print(str1)
		urllib.request.urlopen(op, bytes(str1, 'utf-8'))
		o['orderid'] = "00000000000000000000xxxx"
		#print(o)
def test_op():
	print("hello world!")
	#browser = Browser("firefox")#模拟浏览器
	browser = Browser("chrome")#模拟浏览器
	#browser = Browser()#模拟浏览器
	browser.visit("http://unptest.xiaobalei.com:5288/gbpayserver/mgr/")#访问指定URL
	browser.fill("name", "root")
	browser.fill("pwd", "111111")
	browser.find_by_value("登陆")[0].click()
	browser.find_by_text("计费应用管理").click()
	time.sleep(8)
	browser.quit()

test_op()
