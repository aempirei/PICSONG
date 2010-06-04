#!/bin/bash

if [ ! -f "$1" ]; then
   echo
   echo usage: $0 song.txt
   echo
   exit
fi

code=picsong

a="$1"

echo making picsong

make

echo translating $a into picsong.inc

./picsong < "$a" > picsong.inc

echo compiling "$code"

gpasm "$code.a"
picp -c /dev/ttyS0 12f675 -ef

echo writing "$code.hex"
picp -c /dev/ttyS0 12f675 -wp "$code.hex"
