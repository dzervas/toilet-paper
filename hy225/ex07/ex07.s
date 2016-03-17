

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
	sw		$0, 4($v0)
	jr		$ra

print_node:
	lw		$t0, 4
	slt		$t0, $t1, $a1
