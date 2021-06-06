# start of generated code
	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	4
_bool_tag:
	.word	2
_string_tag:
	.word	3
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const13:
	.word	3
	.word	5
	.word	String_dispTab
	.word	int_const1
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	3
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	3
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"B"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	3
	.word	5
	.word	String_dispTab
	.word	int_const4
	.ascii	"A"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	3
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	3
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	3
	.word	5
	.word	String_dispTab
	.word	int_const2
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	3
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	3
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	3
	.word	7
	.word	String_dispTab
	.word	int_const7
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	3
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	3
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	3
	.word	8
	.word	String_dispTab
	.word	int_const9
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	3
	.word	9
	.word	String_dispTab
	.word	int_const10
	.ascii	"./objectequality.cl"
	.byte	0	
	.align	2
	.word	-1
int_const10:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	19
	.word	-1
int_const9:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const8:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	9
	.word	-1
int_const7:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const6:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const5:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const4:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const3:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const2:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const1:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
int_const0:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	5
	.word	-1
bool_const0:
	.word	2
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	2
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const11
	.word	str_const10
	.word	str_const8
	.word	str_const9
	.word	str_const7
	.word	str_const12
	.word	str_const6
	.word	str_const5
class_objTab:
	.word	B_protObj
	.word	B_init
	.word	A_protObj
	.word	A_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	Int_protObj
	.word	Int_init
	.word	Main_protObj
	.word	Main_init
	.word	IO_protObj
	.word	IO_init
	.word	Object_protObj
	.word	Object_init
B_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A.foo
A_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A.foo
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	-1
B_protObj:
	.word	0
	.word	4
	.word	B_dispTab
	.word	int_const1
	.word	-1
A_protObj:
	.word	1
	.word	4
	.word	A_dispTab
	.word	int_const1
	.word	-1
Bool_protObj:
	.word	2
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
String_protObj:
	.word	3
	.word	5
	.word	String_dispTab
	.word	int_const1
	.word	0
	.word	-1
Int_protObj:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
Main_protObj:
	.word	5
	.word	3
	.word	Main_dispTab
	.word	-1
IO_protObj:
	.word	6
	.word	3
	.word	IO_dispTab
	.word	-1
Object_protObj:
	.word	7
	.word	3
	.word	Object_dispTab
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
A.abort:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A.type_name:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A.copy:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A.foo:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 0($fp)
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
B.abort:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
B.type_name:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
B.copy:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
B.foo:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 0($fp)
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Main.abort:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.type_name:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.copy:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.main:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	li	$a0 0
	la	$a0 B_protObj
	jal	Object.copy
	jal	B_init
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -12($fp)
	move	$s1 $a0
	lw	$a0 -12($fp)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label10
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label10
	la	$a0 bool_const0
	b	label11
label10:
	la	$a0 bool_const1
label11:
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else1
	la	$a0 int_const1
	b	cond_end1
cond_else1:
	move	$a0 $s0
	bne	$a0 $zero label12
	la	$a0 str_const0
	li	$t1 11
	jal	_dispatch_abort
label12:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
cond_end1:
	lw	$a0 -12($fp)
	move	$s1 $a0
	la	$a0 B_protObj
	jal	Object.copy
	jal	B_init
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label13
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label13
	la	$a0 bool_const0
	b	label14
label13:
	la	$a0 bool_const1
label14:
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else2
	move	$a0 $s0
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 12
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	b	cond_end2
cond_else2:
	la	$a0 int_const1
cond_end2:
	la	$a0 A_protObj
	jal	Object.copy
	jal	A_init
	move	$s1 $a0
	la	$a0 A_protObj
	jal	Object.copy
	jal	A_init
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label16
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label16
	la	$a0 bool_const0
	b	label17
label16:
	la	$a0 bool_const1
label17:
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else3
	move	$a0 $s0
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 13
	jal	_dispatch_abort
label18:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	b	cond_end3
cond_else3:
	la	$a0 int_const1
cond_end3:
	li	$a0 0
	lw	$a0 -12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -16($fp)
	move	$s1 $a0
	lw	$a0 -12($fp)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label19
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label19
	la	$a0 bool_const0
	b	label20
label19:
	la	$a0 bool_const1
label20:
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else4
	la	$a0 int_const1
	b	cond_end4
cond_else4:
	move	$a0 $s0
	bne	$a0 $zero label21
	la	$a0 str_const0
	li	$t1 15
	jal	_dispatch_abort
label21:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
cond_end4:
	la	$a0 int_const2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -16($fp)
	bne	$a0 $zero label22
	la	$a0 str_const0
	li	$t1 16
	jal	_dispatch_abort
label22:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$a0 -12($fp)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label23
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label23
	la	$a0 bool_const0
	b	label24
label23:
	la	$a0 bool_const1
label24:
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else5
	la	$a0 int_const1
	b	cond_end5
cond_else5:
	move	$a0 $s0
	bne	$a0 $zero label25
	la	$a0 str_const0
	li	$t1 16
	jal	_dispatch_abort
label25:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
cond_end5:
	addiu	$sp $sp 4
	addiu	$sp $sp 4
	li	$a0 0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	li	$a0 0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 -12($fp)
	move	$s1 $a0
	lw	$a0 -16($fp)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label26
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label26
	la	$a0 bool_const0
	b	label27
label26:
	la	$a0 bool_const1
label27:
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else6
	la	$a0 int_const1
	b	cond_end6
cond_else6:
	move	$a0 $s0
	bne	$a0 $zero label28
	la	$a0 str_const0
	li	$t1 19
	jal	_dispatch_abort
label28:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
cond_end6:
	addiu	$sp $sp 4
	addiu	$sp $sp 4
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
B_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	A_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	la	$a0 int_const0
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	li	$a0 0
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	la	$a0 int_const1
	sw	$a0 12($s0)
	li	$a0 0
	sw	$a0 16($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	li	$a0 0
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	

# end of generated code
