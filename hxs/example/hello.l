#!/usr/local/bin/lxs -s

3403 display char
1110 print H
1301 push 01
1408 add 1
1201 pop 01
2809 cmp 5
2901 if != jmp 01
3300 exit
0001 1
1116 initistr + 5
0072 H
0101 e
0108 l
0108 l
0111 o
0010 \n
