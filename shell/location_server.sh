#!/bin/bash
#while true
#do
#	echo "hell world!"
#	sleep 1;
#done
#counter=0
#echo $counter
#while [ $counter -lt 5 ]
#do
#	counter='expr $counter + 1'
#	echo $counter
#done
# while
#c=0
#while [ $c -lt 3 ]; do
#    c=`expr $c + 1`
#    echo $c
#done
# while读取输入
#echo 'type <CTRL-D> to terminate'
#echo -n 'enter your most liked film: '
#while read FILM; do
#    echo "Yeah! great film the $FILM"
#done

#for
for loop in 1 2 3 4 5; do
    echo "The value is: $loop"
done

for c in 'This is a string'; do
    echo "$c|"
done
for c in This is a string; do
    echo "$c|"
done
for FILE in $HOME/.bash*; do
   echo $FILE
done
for x in one two three four
do
echo number $x
done
#指定分隔符,不起作用
oldIFS=$IFS
IFS=","
for x in one,two,three,four
do
echo number $x
done
IFS=$oldIFS

# until
a=0
until [ ! $a -lt 10 ]
do
   echo $a
   a=`expr $a + 1`
done



