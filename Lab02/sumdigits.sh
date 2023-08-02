#!/bin/bash
#task8.sh

#read in parameter and integer must be entered withim line of command to read this file
num=$1

if [ $# -ne 1 ];
then
	echo "You need to pass one numerical argument."
	exit 1
fi

sum=0

while [ $num -gt 0 ];
do
	let digit=$num%10
	let sum=sum+$digit
	let num=$num/10
done

echo "Sum of digits for given number is $sum."
exit 0
