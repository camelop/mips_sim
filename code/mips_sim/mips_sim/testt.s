	.text
main:
	b a1
a1:
	b a5
a2:
	b a6
a3:
	b a4
a4:
	b a2
a5:
	b a3
a6:
	li $v0 10
	syscall

