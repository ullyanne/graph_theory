#!/bin/bash

# Binários
bellman_ford=./bellman_ford.bin

echo "Testando algoritmo de Bellman-Ford"
for i in ./instances_bm/*.dat
do
	echo -e "\e[33mInstância $i\e[0m";
	$bellman_ford -f $i > temp;

	j=$(basename $i);
	diff -w temp ./answer_bm/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done

echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	$bellman_ford -f $i > temp;

	j=$(basename $i);
	diff -w temp ./sp/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done
