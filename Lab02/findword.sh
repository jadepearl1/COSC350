#!/bin/bash
#task9.sh

echo "This program is meant to find a word in a readable file."

echo "Enter directory."
read direct
#check if directory exists
if [ -d "$direct" ]; then
	echo "Error: no such directory"
	exit 1
fi

#User has three attempts to name a readable file
tries=1
while [ $tries -le 3 ];
do
	echo "Enter readable file name"
	read filename
	
	#check if the file exists, is true file, is readable
	if [ -f "$direct/$filename" ]; then
		if [ -r "$direct/$filename" ]; then
			break
		else
			echo "Error: File not readable."
			exit 2
		fi
	elif [ $tries -eq 3 ]; then
		echo "Error: No such file exists in $direct"
		exit 3
	fi
	let tries=$tries+1
done

echo "Enter word to find in file"
read word

#Search for word in file if found
if grep -q "$word" "$direct/$filename"; then
	echo "$word FOUND!"
else
	echo "Error: $word not found"
	exit 4
fi

exit 0
