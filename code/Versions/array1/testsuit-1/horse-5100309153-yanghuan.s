	.data
	.word 1
_static_71:
	.asciiz "\n"
	.align 2
	.word 13
_static_88:
	.asciiz "no solution!\n"
	.align 2
_static_72:
	.word 0
_static_73:
	.word 0
_static_74:
	.word 0
_static_75:
	.word 0
_static_76:
	.word 0
_static_77:
	.word 0
_static_78:
	.word 0
_static_79:
	.word 0
_static_80:
	.word 0
_static_81:
	.word 0
_static_82:
	.word 0
_static_83:
	.word 0
_static_84:
	.word 0
_static_85:
	.word 0
_static_86:
	.word 0
_static_87:
	.word 0
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
	li $8, 12000
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10

	syscall
	sw $v0, -12($fp)
	li $8, 12000
	lw $9, -12($fp)
	sw $8, 0($9)
	add $10, $9, 4
	sw $10, _static_80
	li $8, 12000
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10

	syscall
	sw $v0, -32($fp)
	li $8, 12000
	lw $9, -32($fp)
	sw $8, 0($9)
	add $10, $9, 4
	sw $10, _static_81
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
	ble $10, $13, _end_if_119
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	sw $10, -8($fp)
_end_if_119:
	li $8, 0
	sw $8, -12($fp)
_begin_loop_90:
	lw $8, -12($fp)
	lw $9, -8($fp)
	bge $8, $9, _end_loop_90
	lw $8, 0($fp)
	lw $9, -12($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	sw $11, -16($fp)
	sw $14, -20($fp)
	beq $11, $14, _end_if_120
	lw $8, -16($fp)
	lw $9, -20($fp)
	slt $10, $8, $9
	move $v0, $10
	sw $10, -76($fp)
	b _end_func_____built_in_string_less
_end_if_120:
_continue_loop90:
	lw $8, -12($fp)
	add $8, $8, 1
	sw $8, -12($fp)
	b _begin_loop_90
_end_loop_90:
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
	beq $10, $13, _end_if_121
	move $v0, $zero
	b _end_func_____built_in_string_equal
_end_if_121:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	li $11, 0
	sw $10, -12($fp)
	sw $11, -8($fp)
_begin_loop_91:
	lw $8, -8($fp)
	lw $9, -12($fp)
	bge $8, $9, _end_loop_91
	lw $8, 0($fp)
	lw $9, -8($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	beq $11, $14, _end_if_122
	move $v0, $zero
	b _end_func_____built_in_string_equal
_end_if_122:
_continue_loop91:
	lw $8, -8($fp)
	add $8, $8, 1
	sw $8, -8($fp)
	b _begin_loop_91
_end_loop_91:
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
	beq $10, $13, _end_if_123
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_inequal
_end_if_123:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	li $11, 0
	sw $10, -12($fp)
	sw $11, -8($fp)
_begin_loop_92:
	lw $8, -8($fp)
	lw $9, -12($fp)
	bge $8, $9, _end_loop_92
	lw $8, 0($fp)
	lw $9, -8($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	beq $11, $14, _end_if_124
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_inequal
_end_if_124:
_continue_loop92:
	lw $8, -8($fp)
	add $8, $8, 1
	sw $8, -8($fp)
	b _begin_loop_92
_end_loop_92:
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
	ble $10, $13, _end_if_125
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	sw $10, -8($fp)
_end_if_125:
	li $8, 0
	sw $8, -12($fp)
_begin_loop_93:
	lw $8, -12($fp)
	lw $9, -8($fp)
	bge $8, $9, _end_loop_93
	lw $8, 0($fp)
	lw $9, -12($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	sw $11, -16($fp)
	sw $14, -20($fp)
	beq $11, $14, _end_if_126
	lw $8, -16($fp)
	lw $9, -20($fp)
	slt $10, $8, $9
	move $v0, $10
	sw $10, -76($fp)
	b _end_func_____built_in_string_less_equal
_end_if_126:
_continue_loop93:
	lw $8, -12($fp)
	add $8, $8, 1
	sw $8, -12($fp)
	b _begin_loop_93
_end_loop_93:
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
	la $8, _static_71
	move $9, $8
	li $v0, 4
	move $a0, $9

	syscall
_end_func_____built_in_println:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -124($fp)
	jr $ra

_func_origin:
	sw $fp, -200($sp)
	add $fp, $sp, -4
	add $sp, $fp, -204
	sw $ra, 0($sp)
	lw $8, 0($fp)
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10

	syscall
	sw $v0, -12($fp)
	lw $8, 0($fp)
	lw $9, -12($fp)
	sw $8, 0($9)
	add $10, $9, 4
	li $11, 0
	sw $10, _static_85
	sw $11, _static_86
_begin_loop_94:
	lw $8, _static_86
	lw $9, 0($fp)
	bge $8, $9, _end_loop_94
	lw $8, 0($fp)
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10

	syscall
	sw $v0, -40($fp)
	lw $8, 0($fp)
	lw $9, -40($fp)
	sw $8, 0($9)
	add $10, $9, 4
	lw $11, _static_86
	mul $12, $11, 4
	lw $13, _static_85
	add $14, $13, $12
	sw $10, 0($14)
	li $15, 0
	sw $15, _static_87
_begin_loop_95:
	lw $8, _static_87
	lw $9, 0($fp)
	bge $8, $9, _end_loop_95
	lw $8, _static_86
	mul $9, $8, 4
	lw $10, _static_85
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, _static_87
	mul $14, $13, 4
	add $15, $12, $14
	sw $zero, 0($15)
_continue_loop95:
	lw $8, _static_87
	add $8, $8, 1
	move $8, $8
	sw $8, _static_87
	b _begin_loop_95
_end_loop_95:
_continue_loop94:
	lw $8, _static_86
	add $8, $8, 1
	move $8, $8
	sw $8, _static_86
	b _begin_loop_94
_end_loop_94:
_end_func_origin:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -196($fp)
	jr $ra

_func_check:
	sw $fp, -140($sp)
	add $fp, $sp, -4
	add $sp, $fp, -144
	sw $ra, 0($sp)
	lw $8, 0($fp)
	lw $9, -4($fp)
	slt $10, $8, $9
	move $11, $10
	sw $11, -8($fp)
	beqz $11, _short_evaluate_5
	lw $8, 0($fp)
	sge $9, $8, 0
	move $10, $9
	sw $10, -8($fp)
_short_evaluate_5:
	lw $8, -8($fp)
	move $v0, $8
	b _end_func_check
_end_func_check:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -136($fp)
	jr $ra

_func_addList:
	sw $fp, -240($sp)
	add $fp, $sp, -4
	add $sp, $fp, -244
	sw $ra, 0($sp)

	lw $8, 0($fp)
	sw $8, -4($sp)

	lw $9, _static_72
	sw $9, -8($sp)

jal _func_check
	sw $v0, -12($fp)
	lw $8, -12($fp)
	move $9, $8
	sw $9, -8($fp)
	beqz $9, _short_evaluate_6

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, _static_72
	sw $9, -8($sp)

jal _func_check
	sw $v0, -16($fp)
	lw $8, -16($fp)
	move $9, $8
	sw $9, -8($fp)
	beqz $9, _short_evaluate_6
	lw $8, 0($fp)
	mul $9, $8, 4
	lw $10, _static_85
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, -4($fp)
	mul $14, $13, 4
	add $15, $12, $14
	lw $16, 0($15)
	seq $17, $16, -1
	move $18, $17
	sw $18, -8($fp)
_short_evaluate_6:
	lw $8, -8($fp)
	beqz $8, _end_if_127
	lw $8, _static_82
	add $9, $8, 1
	mul $8, $9, 4
	lw $10, _static_80
	add $11, $10, $8
	lw $12, 0($fp)
	sw $12, 0($11)
	mul $13, $9, 4
	lw $14, _static_81
	add $15, $14, $13
	lw $16, -4($fp)
	sw $16, 0($15)
	lw $17, _static_84
	add $18, $17, 1
	mul $19, $12, 4
	lw $20, _static_85
	add $21, $20, $19
	lw $22, 0($21)
	mul $23, $16, 4
	add $24, $22, $23
	sw $18, 0($24)
	lw $25, _static_76
	seq $10, $12, $25
	move $8, $10
	sw $8, -104($fp)
	sw $9, _static_82
	beqz $8, _short_evaluate_7
	lw $8, -4($fp)
	lw $9, _static_77
	seq $10, $8, $9
	move $11, $10
	sw $11, -104($fp)
_short_evaluate_7:
	lw $8, -104($fp)
	beqz $8, _end_if_128
	li $8, 1
	sw $8, _static_83
_end_if_128:
_end_if_127:
_end_func_addList:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -236($fp)
	jr $ra

_func_main:
	sw $fp, -412($sp)
	add $fp, $sp, -4
	add $sp, $fp, -416
	sw $ra, 0($sp)

	li $8, 106
	sw $8, -4($sp)

jal _func_origin
	li $v0, 5
	syscall
	sw $v0, -4($fp)
	lw $8, -4($fp)
	sub $9, $8, 1
	move $10, $9
	li $11, 0
	sw $8, _static_72
	sw $9, _static_77
	sw $10, _static_76
	sw $11, _static_86
_begin_loop_96:
	lw $8, _static_86
	lw $9, _static_72
	bge $8, $9, _end_loop_96
	li $8, 0
	sw $8, _static_87
_begin_loop_97:
	lw $8, _static_87
	lw $9, _static_72
	bge $8, $9, _end_loop_97
	lw $8, _static_86
	mul $9, $8, 4
	lw $10, _static_85
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, _static_87
	mul $14, $13, 4
	add $15, $12, $14
	li $16, -1
	sw $16, 0($15)
_continue_loop97:
	lw $8, _static_87
	add $8, $8, 1
	move $8, $8
	sw $8, _static_87
	b _begin_loop_97
_end_loop_97:
_continue_loop96:
	lw $8, _static_86
	add $8, $8, 1
	move $8, $8
	sw $8, _static_86
	b _begin_loop_96
_end_loop_96:
_continue_loop98:
	lw $8, _static_73
	lw $9, _static_82
	bgt $8, $9, _end_loop_98
	lw $8, _static_73
	mul $9, $8, 4
	lw $10, _static_80
	add $11, $10, $9
	lw $12, 0($11)
	mul $13, $8, 4
	lw $14, _static_81
	add $15, $14, $13
	lw $16, 0($15)
	mul $17, $12, 4
	lw $18, _static_85
	add $19, $18, $17
	lw $20, 0($19)
	mul $21, $16, 4
	add $22, $20, $21
	lw $23, 0($22)
	sub $24, $12, 1
	sub $25, $16, 2
	sw $24, -4($sp)
	sw $25, -8($sp)
	sw $12, _static_78
	sw $16, _static_79
	sw $23, _static_84
jal _func_addList
	lw $8, _static_78
	sub $9, $8, 1
	lw $10, _static_79
	add $11, $10, 2
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_78
	add $9, $8, 1
	lw $10, _static_79
	sub $11, $10, 2
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_78
	add $9, $8, 1
	lw $10, _static_79
	add $11, $10, 2
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_78
	sub $9, $8, 2
	lw $10, _static_79
	sub $11, $10, 1
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_78
	sub $9, $8, 2
	lw $10, _static_79
	add $11, $10, 1
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_78
	add $9, $8, 2
	lw $10, _static_79
	sub $11, $10, 1
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_78
	add $9, $8, 2
	lw $10, _static_79
	add $11, $10, 1
	sw $9, -4($sp)
	sw $11, -8($sp)

jal _func_addList
	lw $8, _static_83
	bne $8, 1, _end_if_129
	b _end_loop_98
_end_if_129:
	lw $8, _static_73
	add $9, $8, 1
	sw $9, _static_73
	b _continue_loop98
_end_loop_98:
	lw $8, _static_83
	bne $8, 1, _else_130
	lw $8, _static_76
	mul $9, $8, 4
	lw $10, _static_85
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, _static_77
	mul $14, $13, 4
	add $15, $12, $14
	lw $16, 0($15)
	sw $16, -4($sp)

jal _func_____built_in_toString
	sw $v0, -288($fp)

	lw $8, -288($fp)
	li $v0, 4
	move $a0, $8

	syscall

	la $8, _static_71
	li $v0, 4
	move $a0, $8

	syscall
	b _end_if_130
_else_130:
	la $8, _static_88
	move $9, $8
	li $v0, 4
	move $a0, $9

	syscall
_end_if_130:
	move $v0, $zero
	b _end_func_main
_end_func_main:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -408($fp)
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
