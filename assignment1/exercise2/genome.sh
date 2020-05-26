#!/bin/bash

file="$1"
word="$2"

echo "====================="
# grep -o -i $word $file | wc -l
cat $file | tr -d '\n' | grep -o -i $word | wc -l
echo "====================="

