#!/bin/bash
#task7.sh

#define the factorial by initializing it to 1
fact=1

echo "Enter an integer"
read num

temp=$num

while [ $num -ge 1 ];
do
	let fact=fact*num
	let num--
done

echo "The factorial of the integer $temp is $fact."
exit 0
