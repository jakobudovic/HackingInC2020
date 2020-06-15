#!/bin/bash

# hex to ascii converter online: https://www.rapidtables.com/convert/number/hex-to-ascii.html
# asii table: http://www.asciitable.com/
# looping over string array: https://stackoverflow.com/questions/8880603/loop-through-an-array-of-strings-in-bash

## declare an array variable
declare -a arr=("0x547b465443436948" "0x39786e6554506955" "0x326c4c4d306d507a" "0x4d624c35476e5839" "0x6c78736246564b35" "0x503665514d433071" "0x436f594465383736" "0x475172716365557a" "0x7d737a5457615239")
str=""

## now loop through the above array
for i in "${arr[@]}"
do
   str="${str}$(./reverseaddr $i)"
done

echo $str