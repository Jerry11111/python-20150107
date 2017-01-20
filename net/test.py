import socket
import binascii

def doRequest():
	s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
	s.bind(("lo", 0))
	src_addr = "\x50\x3d\xe5\x0e\x35\x3f"
	dst_addr = "\xff\xff\xff\xff\xff\xff"
	ethertype = "\x08\x06"
	s.send(bytes(dst_addr+src_addr+ethertype+"\x00\x01"+"\x08\x00"+"\x06"+"\x04"+"\x00\x01"+src_addr+"\x7f\x00\x00\x01"+"\x00\x00\x00\x00\x00\x00"+"\x7f\x00\x00\x01", 'utf-8'))

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

	def toBytes(self):
		print(self.dest_mac_u6 + self.sour_mac_u6 + self.frame_type_u2 + self.hard_type_u2 + self.prot_type_u2 + self.mac_len_u1 + self.ip_len_u1 + self.op_u2 + self.send_mac_u6 + self.send_ip_u4 + self.recv_mac_u6 + self.recv_ip_u4)
		return bytearray(self.dest_mac_u6 + self.sour_mac_u6 + self.frame_type_u2 + self.hard_type_u2 + self.prot_type_u2 + self.mac_len_u1 + self.ip_len_u1 + self.op_u2 + self.send_mac_u6 + self.send_ip_u4 + self.recv_mac_u6 + self.recv_ip_u4, 'iso8859-1')

arp = Arp() 
arp.dest_mac_u6 = '\xff\xff\xff\xff\xff\xff';
arp.sour_mac_u6 = '\x08\x00\x27\xbd\xf9\x51'
arp.frame_type_u2 = '\x08\x06'
arp.hard_type_u2 = '\x00\x01'
arp.prot_type_u2 = '\x08\x00'
arp.mac_len_u1 = '\x01'
arp.ip_len_u1 = '\x01'
arp.op_u2 = '\x00\x01'
send_mac_u6 = '\x08\x00\x27\xbd\xf9\x51'
send_ip_u4 = '\x0a\x00\x02\x0f'
recv_mac_u6 = '\x00\x00\x00\x00\x00\x00'
recv_ip_u4 = '\x0a\x00\x02\x02'
arr = arp.toBytes()
print(arr, len(arr))
for a in arr:
	print(hex(a), end = '')
