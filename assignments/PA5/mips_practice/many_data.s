.data 
string1:
    .word 1
    .asciiz "a\n"

.text
main:
la  $a0, string1
addi $a0, $a0, 4
li $v0, 4
syscall
li $v0, 10
syscall

