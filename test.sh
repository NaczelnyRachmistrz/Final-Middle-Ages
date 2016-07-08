#!/bin/bash

if [ $# = 3 ]; then
	flag=1; shift 1
else
	flag=0
fi;
echo -n "" >temp.out;
echo -n "" >tempDiff.out;
echo -n "" >tempErr.out;
echo $flag;
for f in ${2}/*.in; do
	./${1} -v <$f >temp.out 2>tempErr.out;
	pom=`diff temp.out ${f%in}out`;
	pom2=`diff tempErr.out ${f%in}err`;
	firstLetter=${pom:0:1};
	firstLetter2=${pom2:0:1};
	echo -n "$f: stdout: ";
	if [ -z $firstLetter ]; then
		echo -n -e "\e[32mOK!\e[39m;"
	else 
		echo -n -e "Błąd w linii: \e[31m$firstLetter\e[39m;"
	fi;
	if ((flag)); then
		echo -n " stderr: ";
		if [ -z $firstLetter2 ]; then
			echo -n -e " \e[32mOK!\e[39m;"
		else
			echo -n -e "Błąd w linii: \e[31m$firstLetter2\e[39m;"
		fi
	fi;
	echo -n -e "\n"
	done;
	rm temp.out;
	rm tempDiff.out;
	rm tempErr.out	
