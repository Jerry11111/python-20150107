

def list_op():
	t_list = []
	print (t_list, type(t_list))
	length = len(t_list)
	print (length, type(length))
	#t_list[0] = 3 #error 
	# append element
	t_list.append(1)
	t_list.append(2)
	t_list.append('3')
	print (t_list, type(t_list))
	for ele in t_list:
	   print(ele)

def string_op():
	t_string = '123'
	print (t_string, type(t_string))
	# string to byte
	t_array = bytearray(t_string,'utf-8')
	print (t_array, type(t_array))
	t_byte = bytes(t_string, 'utf-8')
	print (t_byte, type(t_byte))
	print (t_array == t_byte)
	# byte to string
	t_string2 = str(t_byte, 'utf-8')
	print (t_string2, type(t_string2))
def dictionary_op():
	t_dic = {'id': 1, 'username': 'admin'}
	t_dic['data'] = '2015-01-13'
	print (t_dic, type(t_dic))
	keys = t_dic.keys()
	for key in keys:
		print(key, t_dic[key])
def test_op():
	print('test')
	count = ['a', 'b', 'b']
	for i in count:
		print(i)
	#for (i = 0; i < 10; i++):
	#	print(i)
	fruits = ['banana', 'apple',  'mango']
	for fruit in fruits:        # Second Example
	   print ('Current fruit :', fruit)
	
#test_op()
#list_op()
string_op()
#dictionary_op()
