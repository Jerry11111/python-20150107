# -*- coding: UTF-8 -*-
import re

print(re.match('www', 'www.runoob.com'))  # 在起始位置匹配
print(re.match('com', 'www.runoob.com'))         # 不在起始位置匹配
#<_sre.SRE_Match object; span=(0, 3), match='www'>
#None

print(re.search('www', 'www.runoob.com'))  # 在起始位置匹配
print(re.search('com', 'www.runoob.com'))         # 不在起始位置匹配
#<_sre.SRE_Match object; span=(0, 3), match='www'>
#<_sre.SRE_Match object; span=(11, 14), match='com'>
