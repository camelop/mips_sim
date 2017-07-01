	.text
main:
	li $v0 9
	li $a0 20
	syscall
	move $t0 $v0
	li $v0 8
	li $a1 20
	move $a0 $t0
	syscall
	li $v0 4
	move $a0 $t0
	syscall
	li $v0 10
	syscall
	