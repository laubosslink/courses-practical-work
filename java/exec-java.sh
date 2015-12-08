#!/bin/bash

#CONF
TP="tp1"

#FONCTIONS
function listPrograms(){
	echo "TP : $TP"
	for file in `ls src/$TP`
	do
		echo "-> ${file%.*}"
	done
}

#SCRIPT
if [ "$1" == "-l" ]
then
	listPrograms
	exit 0
fi

if [ -z "$1" ]
then
	echo "Please Select Program : "
	listPrograms
	
	read -p "Program : " program 
else
	program="$1"
fi

if [ ! -f "src/$TP/$program.java" ]
then
	echo "src/$TP/$program.java doesn't exist"
	exit 1
fi

echo "Compilation..."
javac -d classes -sourcepath src -classpath .:$CLASSPATH `find src -name "*.java"`

echo

if [ "$?" == "0" ]
then

	echo "Execution..."

	echo

	java -classpath .:$CLASSPATH:classes "$TP.$program"

	echo

fi
