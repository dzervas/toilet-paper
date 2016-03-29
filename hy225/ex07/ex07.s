

	.text
	.globl read_int
	.globl node_alloc
	.globl print_node
	.globl search_list
	.globl main

read_int:
	# Read from the OS
	addi	$2, $0, 5
	syscall
	jr		$ra
	
node_alloc:
	# Allocate a new node
	addi	$2, $0, 9
	addi	$a0, $0, 8
	syscall
	# Zero-out the node
	sw		$0, 0($v0)
	sw		$0, 4($v0)
	
	jr		$ra

print_node:
	lw		$t0, 4($a0)
	slt		$t1, $t0, $a1

	# Does this work?
	bne		$t1, $0, $ra

	addi	$2, $0, 1
	add		$a0, $0, $t0
	add		$a1, $0, $0
	syscall
	
	jr		$ra

search_list:
	# s2 is the list and s3 the number
	add		$a0, $0, $s2
	add		$a1, $0, $s3
	jal		print_node

	beq		$ra

main:	
