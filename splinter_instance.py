#-*- coding: utf-8 -*-
#coding=utf-8
from splinter.browser import Browser
b = Browser() 
b.visit("http://www.baidu.com")  ###
b.fill("wd","splinter")
button = b.find_by_id('su')
button.click()
