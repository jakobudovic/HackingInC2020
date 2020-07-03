# Exercise 4, guessing game
## s1049877, Jakob Udovic

Got a bunch of output so I can observe it better by feeding 200 dummy inputs to the service:  
```py
(python -c "for i in range(100) : print('0')") | nc hackme.rded.nl $port | grep had 
```  
After that, I copied and saved it into a file called file.txt.  
Then, I filtered the rows, by trimming the text, keeping only the last column and saving it in a new file `new_file.txt` by using perlx.  

```
cat file.txt | perl -lane 'print $F[-1]' > new_file.txt 
```

After that I sorted the numbers to see max and min value, so I could increase my chances in guessing them:  
```
cat new_file.txt | sort -n > sorted.txt 
```

In `sorted.txt` we have numbers ranging between 27340182252991445 (0x6121C03B48B3D5)
and  
18428075037509633439 (0xFFFFFFFFFFFFFFFF)
which is close to the max value of `ULLONG_MAX`

From now on, I will try to guess the biggest I number I received (18428075037509633439) every time and hope for the best.

--- 

Scrap that, This doesn't work.  
Now I tried with different approach, out of being desparate.  
Maybe, the stored result is somewhere after the input buffer and I could somehow overwrite it.  
Therefore, I would have control over it and could just "guess" the same value as I am overwriting it.  
I will skip the process of how I got the offset for overwriting the result, but in short, it was just feeding the absurd big number of A-s, seeing the result was of the form:   

```
./script.sh 
Guess the number that I have in my mind
You guessed: 1111111111111111111
I had in mind: 4702111234474983745
Too bad, try again
```

After using the online converter from decimal to hex, I saw, that the number `4702111234474983745` (dec) is `4141414141414141` (hex).  
https://www.rapidtables.com/convert/number/decimal-to-hex.html  

Then, I played with the different number of A-s and saw that when inputing too few of them, I would get the "result" number like, `6E000A4141414141`. That means, I did not fully overwrite the value. I found that the sweet spot was a string of length 178.  
```
>>> len("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
178
```  

Because of the reason how values are stored on stack (little endian), I played around by changing the end of the string from `...AAA` to `...CBA` and saw, that the result changes to number (4702394908474949953) `4142434141414141`. I see, that the value gets flipped around, where 41 represents A, 42 B and 43 C in ascii table.  

I realized, I could just stop here and put the value `4702111234474983745` as my guessing value and complete the assignment. So I did that. I just wanted to make sure it's the end of my attack string that controls the result.   

Flag:
```
HiCCTF{vFbAkCEttqb8h9pasZoCZZhGvZXLQq0kszJkteoKRSMMc1dmtPs3JomqG1Epef5k}
```