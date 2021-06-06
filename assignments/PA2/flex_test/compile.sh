#!/bin/bash
flex example.flex
gcc lex.yy.c -ll 
cat example_text.txt | ./a.out
