#!/bin/sh

# if
counter=2
# 等于既可以使用==也可以使用-eq
if [ $counter==2 ];then
 	echo "$counter=2 true"
else 
 	echo "$counter=2 false"
fi

if [ $counter -eq 2 ];then
 	echo "$counter=2 true"
else 
 	echo "$counter=2 false"
fi
# 大于不能使用> 只能使用 -gt
if [ $counter > 2 ];then
 	echo "$counter>2 true"
else 
 	echo "$counter>2 false"
fi
if [ $counter -gt 2 ];then
 	echo "$counter>2 true"
else 
 	echo "$counter>2 false"
fi
# 小于不能使用< 只能使用 -lt
if [ $counter < 2 ];then
 	echo "$counter<2 true"
else 
 	echo "$counter<2 false"
fi
if [ $counter -lt 2 ];then
 	echo "$counter<2 true"
else 
 	echo "$counter<2 false"
fi
# if多分支结构
score=60
if [ $score -lt 60 ]; then
        echo "不及格"
elif [ $score -lt 70 ]; then
        echo "及格"
elif [ $score -lt 80 ]; then
        echo "较好"
elif [ $score -lt 90 ]; then
        echo "良好"
else
        echo "优秀"
fi
