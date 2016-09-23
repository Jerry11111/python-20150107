import urllib.request
def test():
	for i in range(0, 6):
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
test()
