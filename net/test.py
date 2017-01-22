import socket
import binascii

class Arp(object):
	dest_mac_u6 = ''
	sour_mac_u6 = ''
	frame_type_u2 = ''
	hard_type_u2 = ''
	prot_type_u2 = ''
	mac_len_u1 = ''
	ip_len_u1 = ''
	op_u2 = ''
	send_mac_u6 = ''
	send_ip_u4 = ''
	recv_mac_u6 = ''
	recv_ip_u4 = ''
	padding_u18 = '\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

	def toBytes(self):
		return bytearray(self.dest_mac_u6 + self.sour_mac_u6 + self.frame_type_u2 + self.hard_type_u2 + self.prot_type_u2 + self.mac_len_u1 + self.ip_len_u1 + self.op_u2 + self.send_mac_u6 + self.send_ip_u4 + self.recv_mac_u6 + self.recv_ip_u4 + self.padding_u18, 'iso8859-1')
# arp request 广播
def do_arp_request():
	s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
	#s.bind(("lo", 0))
	s.bind(("eth0", 0))
	arp = Arp() 
	arp.dest_mac_u6 = '\xff\xff\xff\xff\xff\xff';
	arp.sour_mac_u6 = '\x08\x00\x27\xbd\xf9\x51'
	arp.frame_type_u2 = '\x08\x06'
	arp.hard_type_u2 = '\x00\x01'
	arp.prot_type_u2 = '\x08\x00'
	arp.mac_len_u1 = '\x06'
	arp.ip_len_u1 = '\x04'
	arp.op_u2 = '\x00\x01'
	arp.send_mac_u6 = '\x08\x00\x27\xbd\xf9\x51'
	arp.send_ip_u4 = '\x0a\x00\x02\x0f'
	arp.recv_mac_u6 = '\x00\x00\x00\x00\x00\x00'
	arp.recv_ip_u4 = '\x0a\x00\x02\x02'
	#arp.recv_ip_u4 = '\x0a\x00\x02\x01'
	arr = arp.toBytes()
	print(arr, len(arr))
	for a in arr:
		print(hex(a), end = '')
	s.send(arr)
# arp reple 广播
def do_arp_reply():
	s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
	s.bind(("eth0", 0))
	arp = Arp() 
	arp.dest_mac_u6 = '\xff\xff\xff\xff\xff\xff';
	arp.sour_mac_u6 = '\x08\x00\x27\xbd\xf9\x51'
	arp.frame_type_u2 = '\x08\x06'
	arp.hard_type_u2 = '\x00\x01'
	arp.prot_type_u2 = '\x08\x00'
	arp.mac_len_u1 = '\x06'
	arp.ip_len_u1 = '\x04'
	arp.op_u2 = '\x00\x02'
	arp.send_mac_u6 = '\x08\x00\x27\xbd\xf9\x51'
	arp.send_ip_u4 = '\x0a\x00\x02\x0f'
	arp.recv_mac_u6 = '\xff\xff\xff\xff\xff\xff'
	arp.recv_ip_u4 = '\x0a\x00\x02\x02'
	#arp.recv_ip_u4 = '\x0a\x00\x02\x01'
	arr = arp.toBytes()
	print(arr, len(arr))
	for a in arr:
		print(hex(a), end = '')
	s.send(arr)
do_arp_reply()
