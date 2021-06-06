.data 
request_text: .asciiz "Please enter 2 integers\n"
output_text:  .asciiz "The answer is "
new_line:     .asciiz "\n"

.text

main:
li $a0, 7
sw $a0, ($sp)

li $v0, 4
la $a0, request_text
syscall

li $v0, 5
syscall
move $a0, $v0
li $v0, 5
syscall
move $a1, $v0

jal add_func
move $a1, $a0
lw   $a2, ($sp)
add  $a1, $a1, $a2

li $v0, 4
la $a0, output_text
syscall

li $v0, 1
move $a0, $a1 
syscall

li $v0, 4
la $a0, new_line
syscall
j program_end

add_func:
add  $a0, $a0, $a1
jr		$ra					# jump to $ra

program_end:
li		$v0, 	10	# $v0 = 
syscall