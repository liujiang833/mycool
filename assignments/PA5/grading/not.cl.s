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
	.word	1
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
str_const11:
	.word	1
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	1
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	1
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	1
	.word	6
	.word	String_dispTab
	.word	int_const3
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	1
	.word	5
	.word	String_dispTab
	.word	int_const5
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	1
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	1
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	1
	.word	7
	.word	String_dispTab
	.word	int_const7
	.ascii	"_prim_slot"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	1
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"SELF_TYPE"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	1
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"_no_class"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	1
	.word	8
	.word	String_dispTab
	.word	int_const9
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	1
	.word	7
	.word	String_dispTab
	.word	int_const10
	.ascii	"./not.cl"
	.byte	0	
	.align	2
	.word	-1
int_const10:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	8
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
	.word	3
	.word	-1
int_const4:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	6
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
	.word	1
	.word	-1
int_const1:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	100
	.word	-1
int_const0:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
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
	.word	str_const10
	.word	str_const9
	.word	str_const8
	.word	str_const6
	.word	str_const7
	.word	str_const5
class_objTab:
	.word	Main_protObj
	.word	Main_init
	.word	String_protObj
	.word	String_init
	.word	Bool_protObj
	.word	Bool_init
	.word	IO_protObj
	.word	IO_init
	.word	Int_protObj
	.word	Int_init
	.word	Object_protObj
	.word	Object_init
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Main.main
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	-1
Main_protObj:
	.word	0
	.word	3
	.word	Main_dispTab
	.word	-1
String_protObj:
	.word	1
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
Bool_protObj:
	.word	2
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	3
	.word	3
	.word	IO_dispTab
	.word	-1
Int_protObj:
	.word	4
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
Object_protObj:
	.word	5
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
	la	$a0 int_const0
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 bool_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
loop_begin1:
	lw	$a0 -12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	lw	$t1 4($sp)
	lw	$t1 12($t1)
	lw	$a0 12($a0)
	blt	$t1 $a0 label10
	la	$a0 bool_const0
	b	label11
label10:
	la	$a0 bool_const1
label11:
	addiu	$sp $sp 4
	lw	$a0 12($a0)
	beq	$a0 $zero loop_end1
	lw	$a0 -16($fp)
	move	$s1 $a0
	lw	$a0 -16($fp)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label12
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label12
	la	$a0 bool_const0
	b	label13
label12:
	la	$a0 bool_const1
label13:
	lw	$a0 -16($fp)
	move	$s1 $a0
	lw	$a0 -16($fp)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label14
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label14
	la	$a0 bool_const0
	b	label15
label14:
	la	$a0 bool_const1
label15:
	lw	$a0 -16($fp)
	move	$s1 $a0
	lw	$a0 -16($fp)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
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
	lw	$a0 -16($fp)
	move	$s1 $a0
	lw	$a0 -16($fp)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label18
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label18
	la	$a0 bool_const0
	b	label19
label18:
	la	$a0 bool_const1
label19:
	lw	$a0 -16($fp)
	move	$s1 $a0
	lw	$a0 -16($fp)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$t1 12($a0)
	li	$t2 -1
	xor	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$t2 $a0
	move	$t1 $s1
	sub	$t3 $t1 $t2
	beq	$t3 $zero label20
	li	$a0 0
	li	$a1 1
	jal	equality_test
	beq	$a0 $zero label20
	la	$a0 bool_const0
	b	label21
label20:
	la	$a0 bool_const1
label21:
	lw	$a0 -12($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const0
	jal	Object.copy
	lw	$t2 8($sp)
	lw	$t2 12($t2)
	lw	$t3 4($sp)
	lw	$t3 12($t3)
	add	$t2 $t2 $t3
	sw	$t2 12($a0)
	addiu	$sp $sp 8
	sw	$a0 -12($fp)
	b	loop_begin1
loop_end1:
	lw	$a0 -16($fp)
	lw	$a0 12($a0)
	beq	$a0	$zero	cond_else1
	move	$a0 $s0
	bne	$a0 $zero label22
	la	$a0 str_const0
	li	$t1 18
	jal	_dispatch_abort
label22:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	b	cond_end1
cond_else1:
	la	$a0 int_const0
cond_end1:
	addiu	$sp $sp 4
	addiu	$sp $sp 4
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
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 12
	move	$s0 $a0
	jal	Object_init
	la	$a0 int_const0
	sw	$a0 12($s0)
	li	$a0 0
	sw	$a0 16($s0)
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
