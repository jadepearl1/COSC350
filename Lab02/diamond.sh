#!/bin/sh
#task6a.sh

base=0
valid=0

#input validation
while [ $valid -eq 0 ]; do
	echo "Enter an odd value greater than 3."
	read base
	#check if the base is odd and greater than 3
	if [ $base -gt 3 ] && [ `expr $base % 2` -eq 1 ]; then
		valid=1
	fi
done

#drawing the first half of the diamond
for i in $(seq 1 2 $base) #increment by 2 until the value of base is reached. this prints the diamond in * here it increases by 2 * every iteration
do
	for j in $(seq $base -2 $i) #decrement by 2 until value of i is reached to print spaces
	do
		echo -n " "
	done
	for k in $(seq 1 $i) #increment until i is reached to print *
	do
		echo -n "*"
	done
	echo ""
done

#drawing second half of diamond
for i in $(seq `expr $base - 2` -2 1) #decrease base by 2 until 1 * is printed
do
	for j in $(seq $base -2 $i)
	do
		echo -n " "
	done
	for k in $(seq 1 $i)
	do
		echo -n "*"
	done 
	echo ""
done
