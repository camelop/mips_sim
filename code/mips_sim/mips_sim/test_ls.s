	.text
main:
	li $v0 9
	li $a0 20
	syscall
	li $8 12345
	
	move $10 $v0
	sw $8 -20($sp)
	lw $9 -21($sp)
	move $a0 $9
	li $v0 1
	syscall
	li $v0 10
	syscall
	
	