#coding=UTF-8
import re
 
# 将正则表达式编译成Pattern对象
pattern = re.compile(r'hello')
 
# 使用Pattern匹配文本，获得匹配结果，无法匹配时将返回None
match = pattern.match('hello world!')
 
if match:
    # 使用Match获得分组信息
    print match.group()
def get_pic_src():
    p = re.compile(r'<img[^>]*src[=\'\"\s]+([^\"\']*)[\"\']?[^>]*>', re.I)
    text = '<p><img alt=\"\" src=\"/uploads/ckeditor/pictures/7/content_1234594100532399625.jpg\" style=\"width: 700px; height: 560px;\" />132<img alt=\"\" src=\"/uploads/ckeditor/pictures/8/content_1901904_140154707195_2.jpg\" style=\"width: 800px; height: 531px;\" /></p>\r\n';
    r = p.findall(text) 
    print r
get_pic_src()
