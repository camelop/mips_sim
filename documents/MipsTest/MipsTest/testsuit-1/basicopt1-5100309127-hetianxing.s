	.data
	.word 1
_static_6:
	.asciiz "\n"
	.align 2
	.data
_buffer:
	.word 0
	.text
_buffer_init:
	li $a0, 256
	li $v0, 9
	syscall
	sw $v0, _buffer
	jr $ra
	.text
main:
	jal _buffer_init
	add $fp, $zero, $sp
	jal _func_main
	move $a0, $v0
	li $v0, 17
	syscall
_func_____built_in_string_less:
	sw $fp, -212($sp)
	add $fp, $sp, -4
	add $sp, $fp, -216
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	sw $10, -8($fp)
	ble $10, $13, _end_if_16
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	sw $10, -8($fp)
_end_if_16:
	li $8, 0
	sw $8, -12($fp)
_begin_loop_15:
	lw $8, -12($fp)
	lw $9, -8($fp)
	bge $8, $9, _end_loop_15
	lw $8, 0($fp)
	lw $9, -12($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	sw $11, -16($fp)
	sw $14, -20($fp)
	beq $11, $14, _end_if_17
	lw $8, -16($fp)
	lw $9, -20($fp)
	slt $10, $8, $9
	move $v0, $10
	sw $10, -76($fp)
	b _end_func_____built_in_string_less
_end_if_17:
_continue_loop15:
	lw $8, -12($fp)
	add $8, $8, 1
	sw $8, -12($fp)
	b _begin_loop_15
_end_loop_15:
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -8($fp)
	slt $12, $11, $10
	move $v0, $12
	sw $12, -88($fp)
	b _end_func_____built_in_string_less
_end_func_____built_in_string_less:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -208($fp)
	jr $ra

_func_____built_in_string_equal:
	sw $fp, -188($sp)
	add $fp, $sp, -4
	add $sp, $fp, -192
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	beq $10, $13, _end_if_18
	move $v0, $zero
	b _end_func_____built_in_string_equal
_end_if_18:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	li $11, 0
	sw $10, -12($fp)
	sw $11, -8($fp)
_begin_loop_16:
	lw $8, -8($fp)
	lw $9, -12($fp)
	bge $8, $9, _end_loop_16
	lw $8, 0($fp)
	lw $9, -8($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	beq $11, $14, _end_if_19
	move $v0, $zero
	b _end_func_____built_in_string_equal
_end_if_19:
_continue_loop16:
	lw $8, -8($fp)
	add $8, $8, 1
	sw $8, -8($fp)
	b _begin_loop_16
_end_loop_16:
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_equal
_end_func_____built_in_string_equal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -184($fp)
	jr $ra

_func_____built_in_string_inequal:
	sw $fp, -188($sp)
	add $fp, $sp, -4
	add $sp, $fp, -192
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	beq $10, $13, _end_if_20
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_inequal
_end_if_20:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	li $11, 0
	sw $10, -12($fp)
	sw $11, -8($fp)
_begin_loop_17:
	lw $8, -8($fp)
	lw $9, -12($fp)
	bge $8, $9, _end_loop_17
	lw $8, 0($fp)
	lw $9, -8($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	beq $11, $14, _end_if_21
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_inequal
_end_if_21:
_continue_loop17:
	lw $8, -8($fp)
	add $8, $8, 1
	sw $8, -8($fp)
	b _begin_loop_17
_end_loop_17:
	move $v0, $zero
	b _end_func_____built_in_string_inequal
_end_func_____built_in_string_inequal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -184($fp)
	jr $ra

_func_____built_in_string_greater:
	sw $fp, -132($sp)
	add $fp, $sp, -4
	add $sp, $fp, -136
	sw $ra, 0($sp)

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, 0($fp)
	sw $9, -8($sp)

jal _func_____built_in_string_less
	sw $v0, -8($fp)
	lw $8, -8($fp)
	move $v0, $8
	b _end_func_____built_in_string_greater
_end_func_____built_in_string_greater:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -128($fp)
	jr $ra

_func_____built_in_string_less_equal:
	sw $fp, -220($sp)
	add $fp, $sp, -4
	add $sp, $fp, -224
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	sw $10, -8($fp)
	ble $10, $13, _end_if_22
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	sw $10, -8($fp)
_end_if_22:
	li $8, 0
	sw $8, -12($fp)
_begin_loop_18:
	lw $8, -12($fp)
	lw $9, -8($fp)
	bge $8, $9, _end_loop_18
	lw $8, 0($fp)
	lw $9, -12($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	sw $11, -16($fp)
	sw $14, -20($fp)
	beq $11, $14, _end_if_23
	lw $8, -16($fp)
	lw $9, -20($fp)
	slt $10, $8, $9
	move $v0, $10
	sw $10, -76($fp)
	b _end_func_____built_in_string_less_equal
_end_if_23:
_continue_loop18:
	lw $8, -12($fp)
	add $8, $8, 1
	sw $8, -12($fp)
	b _begin_loop_18
_end_loop_18:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	sle $14, $10, $13
	move $v0, $14
	sw $14, -96($fp)
	b _end_func_____built_in_string_less_equal
_end_func_____built_in_string_less_equal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -216($fp)
	jr $ra

_func_____built_in_string_greater_equal:
	sw $fp, -132($sp)
	add $fp, $sp, -4
	add $sp, $fp, -136
	sw $ra, 0($sp)

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, 0($fp)
	sw $9, -8($sp)

jal _func_____built_in_string_less_equal
	sw $v0, -8($fp)
	lw $8, -8($fp)
	move $v0, $8
	b _end_func_____built_in_string_greater_equal
_end_func_____built_in_string_greater_equal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -128($fp)
	jr $ra

_func_____built_in_println:
	sw $fp, -128($sp)
	add $fp, $sp, -4
	add $sp, $fp, -132
	sw $ra, 0($sp)

	lw $8, 0($fp)
	li $v0, 4
	move $a0, $8

	syscall
	la $8, _static_6
	move $9, $8
	li $v0, 4
	move $a0, $9

	syscall
_end_func_____built_in_println:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -124($fp)
	jr $ra

_func_main:
	sw $fp, -432($sp)
	add $fp, $sp, -4
	add $sp, $fp, -436
	sw $ra, 0($sp)
	li $8, 100
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10

	syscall
	sw $v0, -36($fp)
	li $8, 100
	lw $9, -36($fp)
	sw $8, 0($9)
	add $10, $9, 4
	li $11, 0
	sw $10, 0($fp)
	sw $11, -4($fp)
_begin_loop_19:
	lw $8, -4($fp)
	bge $8, 100, _end_loop_19
	li $8, 100
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10

	syscall
	sw $v0, -72($fp)
	li $8, 100
	lw $9, -72($fp)
	sw $8, 0($9)
	add $10, $9, 4
	lw $11, -4($fp)
	mul $12, $11, 4
	lw $13, 0($fp)
	add $14, $13, $12
	sw $10, 0($14)
_continue_loop19:
	lw $8, -4($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -4($fp)
	b _begin_loop_19
_end_loop_19:
	li $8, 0
	li $9, 0
	sw $8, -12($fp)
	sw $9, -4($fp)
_begin_loop_20:
	lw $8, -4($fp)
	bge $8, 100, _end_loop_20
	li $8, 0
	sw $8, -8($fp)
_begin_loop_21:
	lw $8, -8($fp)
	bge $8, 100, _end_loop_21
	lw $8, -4($fp)
	mul $9, $8, 4
	lw $10, 0($fp)
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, -8($fp)
	mul $14, $13, 4
	add $15, $12, $14
	sw $zero, 0($15)
_continue_loop21:
	lw $8, -8($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -8($fp)
	b _begin_loop_21
_end_loop_21:
_continue_loop20:
	lw $8, -4($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -4($fp)
	b _begin_loop_20
_end_loop_20:
	li $8, 0
	sw $8, -4($fp)
_begin_loop_22:
	lw $8, -4($fp)
	bge $8, 100, _end_loop_22
	lw $8, -4($fp)
	sgt $9, $8, 20
	move $10, $9
	sw $10, -136($fp)
	beqz $10, _short_evaluate_0
	lw $8, -4($fp)
	slt $9, $8, 80
	move $10, $9
	sw $10, -136($fp)
_short_evaluate_0:
	lw $8, -136($fp)
	beqz $8, _end_if_24
	li $8, 0
	sw $8, -8($fp)
_begin_loop_23:
	lw $8, -8($fp)
	bge $8, 100, _end_loop_23
	lw $8, -8($fp)
	sgt $9, $8, 5
	move $10, $9
	sw $10, -164($fp)
	bnez $10, _short_evaluate_1
	lw $8, -4($fp)
	slt $9, $8, 90
	move $10, $9
	sw $10, -164($fp)
_short_evaluate_1:
	lw $8, -164($fp)
	beqz $8, _end_if_25
	lw $8, -8($fp)
	mul $9, $8, 4
	div $10, $9, 100
	mul $11, $8, 4
	rem $12, $11, 100
	add $13, $8, 50
	lw $14, -4($fp)
	add $15, $14, $10
	mul $16, $15, 4
	lw $17, 0($fp)
	add $18, $17, $16
	lw $19, 0($18)
	mul $20, $12, 4
	add $21, $19, $20
	sw $13, 0($21)
	sw $10, -16($fp)
	sw $12, -20($fp)
_end_if_25:
_continue_loop23:
	lw $8, -8($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -8($fp)
	b _begin_loop_23
_end_loop_23:
_end_if_24:
_continue_loop22:
	lw $8, -4($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -4($fp)
	b _begin_loop_22
_end_loop_22:
	li $8, 0
	sw $8, -4($fp)
_begin_loop_24:
	lw $8, -4($fp)
	bge $8, 100, _end_loop_24
	li $8, 0
	sw $8, -8($fp)
_begin_loop_25:
	lw $8, -8($fp)
	bge $8, 100, _end_loop_25
	lw $8, -4($fp)
	mul $9, $8, 4
	lw $10, 0($fp)
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, -8($fp)
	mul $14, $13, 4
	add $15, $12, $14
	lw $16, 0($15)
	lw $17, -12($fp)
	add $18, $17, $16
	sw $18, -12($fp)
_continue_loop25:
	lw $8, -8($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -8($fp)
	b _begin_loop_25
_end_loop_25:
_continue_loop24:
	lw $8, -4($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, -4($fp)
	b _begin_loop_24
_end_loop_24:

	lw $8, -12($fp)
	sw $8, -4($sp)

jal _func_____built_in_toString
	sw $v0, -308($fp)

	lw $8, -308($fp)
	li $v0, 4
	move $a0, $8

	syscall

	la $8, _static_6
	li $v0, 4
	move $a0, $8

	syscall
_end_func_main:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -428($fp)
	jr $ra

	.text
_string_copy:
	_begin_string_copy:
	lb $v0, 0($a0)
	beqz $v0, _exit_string_copy
	sb $v0, 0($a1)
	add $a0, $a0, 1
	add $a1, $a1, 1
	j _begin_string_copy
	_exit_string_copy:
	sb $zero, 0($a1)
	jr $ra

_func_____built_in_substring:
	lw $a0, -4($sp)
	lw $a1, -8($sp)
	lw $a2, -12($sp)
	subu $sp, $sp, 4
	sw $ra, 0($sp)

	move $t0, $a0

	sub $t1, $a2, $a1
	add $t1, $t1, 1
	add $a0, $t1, 5
	li $v0, 9
	syscall
	sw $t1, 0($v0)
	add $v0, $v0, 4

	add $a0, $t0, $a1
	add $t2, $t0, $a2
	lb $t3, 1($t2)
	sb $zero, 1($t2)
	move $a1, $v0
	move $t4, $v0
	jal _string_copy
	move $v0, $t4
	sb $t3, 1($t2)

	lw $ra, 0($sp)
	addu $sp, $sp, 4
	jr $ra

_count_string_length:
	move $v0, $a0

	_begin_count_string_length:
	lb $v1, 0($a0)
	beqz $v1, _exit_count_string_length
	add $a0, $a0, 1
	j _begin_count_string_length

	_exit_count_string_length:
	sub $v0, $a0, $v0
	jr $ra

_func_____built_in_getString:
	subu $sp, $sp, 4
	sw $ra, 0($sp)

	lw $a0, _buffer
	li $a1, 255
	li $v0, 8
	syscall

	jal _count_string_length

	move $a1, $v0
	add $a0, $v0, 5
	li $v0, 9
	syscall
	sw $a1, 0($v0)
	add $v0, $v0, 4
	lw $a0, _buffer
	move $a1, $v0
	move $t0, $v0
	jal _string_copy
	move $v0, $t0

	lw $ra, 0($sp)
	addu $sp, $sp, 4
	jr $ra

_func_____built_in_parseInt:
	lw $a0, -4($sp)
	li $v0, 0
	move $t0, $a0
	li $t2, 1

	_count_number_pos:
	lb $t1, 0($t0)
	bgt $t1, 57, _begin_parse_int
	blt $t1, 48, _begin_parse_int
	add $t0, $t0, 1
	j _count_number_pos

	_begin_parse_int:
	sub $t0, $t0, 1

	_parsing_int:
	blt $t0, $a0, _finish_parse_int
	lb $t1, 0($t0)
	sub $t1, $t1, 48
	mul $t1, $t1, $t2
	add $v0, $v0, $t1
	mul $t2, $t2, 10
	sub $t0, $t0, 1
	j _parsing_int

	_finish_parse_int:
	jr $ra

_func_____built_in_string_concatenate:
	lw $a0, -4($sp)
	lw $a1, -8($sp)
	subu $sp, $sp, 4
	sw $ra, 0($sp)

	move $t2, $a0
	move $t3, $a1

	lw $t0, -4($a0)
	lw $t1, -4($a1)
	add $t5, $t0, $t1
	add $a0, $t5, 5
	li $v0, 9
	syscall
	sw $t5, 0($v0)
	add $v0, $v0, 4
	move $t4, $v0

	move $a0, $t2
	move $a1, $t4
	jal _string_copy

	move $a0, $t3
	add $a1, $t4, $t0
	
	jal _string_copy

	move $v0, $t4
	lw $ra, 0($sp)
	addu $sp, $sp, 4
	jr $ra

_func_____built_in_toString:
	lw $a0, -4($sp)
	li $t0, 0
	bgez $a0, _skip_set_less_than_zero
	li $t0, 1
	neg $a0, $a0
	_skip_set_less_than_zero:
	beqz $a0, _set_zero

	li $t1, 0
	move $t2, $a0
	move $t3, $a0
	li $t5, 10

	_begin_count_digit:
	div $t2, $t5
	mflo $v0
	mfhi $v1
	bgtz $v0, _not_yet
	bgtz $v1, _not_yet
	j _yet
	_not_yet:
	add $t1, $t1, 1
	move $t2, $v0
	j _begin_count_digit

	_yet:
	beqz $t0, _skip_reserve_neg
	add $t1, $t1, 1
	_skip_reserve_neg:
	add $a0, $t1, 5
	li $v0, 9
	syscall
	sw $t1, 0($v0)
	add $v0, $v0, 4
	add $t1, $t1, $v0
	sb $zero, 0($t1)
	sub $t1, $t1, 1

	_continue_toString:
	div $t3, $t5
	mfhi $v1
	add $v1, $v1, 48
	sb $v1, 0($t1)
	sub $t1, $t1, 1
	mflo $t3
	
	bnez $t3, _continue_toString

	beqz $t0, _skip_place_neg
	li $v1, 45
	sb $v1, 0($t1)
	_skip_place_neg:
	
	jr $ra

	_set_zero:
	li $a0, 6
	li $v0, 9
	syscall
	li $a0, 1
	sw $a0, 0($v0)
	add $v0, $v0, 4
	li $a0, 48
	sb $a0, 0($v0)
	jr $ra
