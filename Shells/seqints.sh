#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Need an integer to add"
	exit 1
fi
sum=0
for input in $@
do
	sum=`expr $sum + $input`
done
echo "Sum of arguments is "$sum"."
exit 0
