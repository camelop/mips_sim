	.text
main:
	li $8, 45
	li $9, 7
	div $8, $9
	li $v0, 1
	mfhi $a0
	syscall
	mflo $a0
	syscall
	li $v0, 10
	syscall
	
	