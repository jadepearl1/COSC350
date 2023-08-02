#!/bin/sh
#task6c.sh

base=0
valid=0
arrTail=0

#input validation
while [ $valid -eq 0 ]; do
	echo "Enter an odd value greater than 3."
	read base
	#check if the base is odd and greater than 3
	if [ $base -gt 3 ] && [ `expr $base % 2` -eq 1 ]; then
		valid=1
	fi
done

echo "Enter the length of the arrow tail"
read arrTail

#drawing the top half of the arrow
for i in $(seq 1 2 $base) #increment i by 2 until i=base value
do
	#if i=base, then print the tail and then the base, if not, print arrTail # spaces instead then the proper number of stars
	if [ $i -eq $base ]; then
		for m in $(seq 1 $arrTail)
		do
			echo -n "*"
		done
	else
		for j in $(seq 1 $arrTail)
		do
			echo -n " "
		done
	fi

	#print a * until k=i
	for k in $(seq 1 $i)
	do
		echo -n "*"
	done
	#print new line
	echo
done

#drawing second half of arrow
for i in $(seq `expr $base - 2` -2 1) #decrease base by 2 until 1 * is printed
do
	for j in $(seq 1 $arrTail) #increase j by 1 until it = arrTail to print arrTail # spaces
	do
		echo -n " "
	done
	for k in $(seq 1 $i) #increase k by 1 til = 1 to print i *
	do
		echo -n "*"
	done 
	echo
done

exit 0
