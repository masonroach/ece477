#!/bin/bash
if [ "$1" == "on" ]
then 
	.~/ECE477/ece477/lab2/lab2
fi
if [ "$1" == "off" ]
then
	ps ajxf | grep "./lab2" | head -n 1 | awk '{system ("kill -KILL " $3)}'
fi
