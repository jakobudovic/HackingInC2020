#!/bin/bash

#source: https://blog.eduonix.com/shell-scripting/generating-random-numbers-in-linux-shell-scripting/
# https://linuxize.com/post/bash-if-else-statement/

#ACGT
# initialisation of the randomizer (seeding)
RANDOM=$$
for (( i=0; i<500; i++))
do
        for (( j=0; j<100; j++ ))
        do
                # random is between 0 and 32767, we limit it here from 0-3 and add 1 so it's 1-4
                num=$(( ( RANDOM % 4 )  + 1 ))

                if [[ $num -eq 1 ]]
                then
                       printf "A"
                elif [[ $num -eq 2 ]]
                then
                        printf "C"
                elif [[ $num -eq 3 ]]
                then
                        printf "G"
                else
                        printf "T"
                fi
        done
        printf "\n"
done


