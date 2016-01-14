import urllib.request

def do_get(url, headers = {}):
	op = urllib.request.Request(url)
	for key in headers:
		print(key, headers[key])
		op.add_header(key, headers[key])
	resp = urllib.request.urlopen(op)
	bdata = resp.read()
	return bdata
def do_post(url, data = {}, headers = {}):
	post_data = urllib.parse.urlencode(data)
	print(post_data)
	op = urllib.request.Request(url)
	for key in headers:
		print(key, headers[key])
		op.add_header(key, headers[key])
	resp = urllib.request.urlopen(op, bytes(post_data, 'utf-8'))
	bdata = resp.read()
	return bdata
url = 'http://www.baidu.com/'
headers={'i': '1', 'j': '2'}
data={'id': 1, 'username': 'admin'}
#data = do_get(url, headers)
#data = do_post(url, data, headers)
data = do_post(url, headers = headers)
print (type(data))

