.data
hello_world: .asciiz "Hello World!\n"

.text
main:
li  $t1, 1
li  $t2, 1
xor $a0 $t1 $t2
#jal out_hello_word
li $v0, 1
syscall

label0:
li		$v0, 	10	# $v0 = 
syscall

#out_hello_word:
#li		$v0, 	4	# $v0 = 4
#la		$a0, hello_world	 
#syscall
#jr		$ra					# jump to $ra



