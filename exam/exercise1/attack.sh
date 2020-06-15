#!/bin/bash

SCRIPT_PATH="/home/jakob/Documents/git/HackingInC2020/exam/exercise1/reverseaddr"

# hex to ascii converter online: https://www.rapidtables.com/convert/number/hex-to-ascii.html
# asii table: http://www.asciitable.com/
# looping over string array: https://stackoverflow.com/questions/8880603/loop-through-an-array-of-strings-in-bash
# 


## declare an array variable
# declare -a arr=("0x8080808080808080" "0x7fffffffebb7" "0" "0xfefefefefefefeff" "0x7ffff7ffc645" "0x4869434354467b57" "0x30456b6f75526c52" "0x346659586f705766" "0x58696f774f667339" "0x4f4d687968326746" "0x704f6e724d6e494d" "0x42514e694b515553" "0x5331454c704d4953" "0x61546b5a5030377d" "0x1")
declare -a arr=("0x4869434354467b57" "0x30456b6f75526c52" "0x346659586f705766" "0x58696f774f667339" "0x4f4d687968326746" "0x704f6e724d6e494d" "0x42514e694b515553" "0x5331454c704d4953" "0x61546b5a5030377d" "0x1")
str=""

## now loop through the above array
for i in "${arr[@]}"
do
   # temp="${$SCRIPT_PATH $i}"
   echo $i
   # echo $(./reverseaddr $i)
   # str="${str}$(./reverseaddr $i)"
   # echo 
   # or do whatever with individual element of the array
done


echo $str
