#!/bin/sh
#task6b.sh

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
	#j=base and decrements by 1 until it is equal to 1 to print spaces
	for j in $(seq $base -1 $i)
	do
		echo -n " "
	done
	#print a * until k=i
	for k in $(seq 1 $i) #increment until i is reached to print *
	do
		echo -n "*"
	done
	#print new line IF tail line isnt reached yet
	if [ $i -eq $base ]; then
		echo -n
	else
		echo
	fi
done

#printing the tail
for i in $(seq 1 $arrTail)
do
	echo -n "*"
	if [ $i -eq $arrTail ]; then
		echo
	fi
done

#drawing second half of arrow
for i in $(seq `expr $base - 2` -2 1) #decrease base by 2 until 1 * is printed
do
	for j in $(seq $base -1 $i)
	do
		echo -n " "
	done
	for k in $(seq 1 $i)
	do
		echo -n "*"
	done 
	echo ""
done

exit 0
