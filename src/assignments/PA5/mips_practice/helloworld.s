.data
hello_world: .asciiz "Hello World!\n"

.text
main:
jal out_hello_word
li		$v0, 	10	# $v0 = 
syscall

out_hello_word:
li		$v0, 	4	# $v0 = 4
la		$a0, hello_world	 
syscall
jr		$ra					# jump to $ra



