	.text
	.globl read_int
	.globl node_alloc
	.globl print_node
	.globl search_list
	.globl main

# $s0 head of the list

# Returns integer ($v0)
read_int:
	# Read from the OS
	addi	$v0, $0, 5
	syscall

	jr		$ra

# Returns allocated node address ($v0)
node_alloc:
	# Allocate a new node
	addi	$v0, $0, 9
	addi	$a0, $0, 8
	syscall

	# Zero-out the node
	sw		$0, 0($v0)
	sw		$0, 4($v0)

	jr		$ra

# Params: $s2 address of node, $s1 integer to compare
print_node:
	lw		$t0, 0($s2)
	slt		$t1, $t0, $s1

	beq		$t1, $0, print_node_exit

	addi	$v0, $0, 1
	add		$a0, $0, $t0
	add		$a1, $0, $0
	syscall

print_node_exit:
	jr		$ra

# Params: $s2 current head of list, $s1 integer to search
search_list:
	# Save $a0 and $ra. They're used by print_node later.
	add		$s3, $0, $ra

search_list_loop:
	jal		print_node

	lw		$t0, 4($s2)
	addi	$s2, $s2, 8

	bne		$t0, $0, search_list_loop
	jr		$s3

main:
	jal node_alloc
	add		$s0, $0, $v0
	add		$s1, $0, $v0

main_loop:
	jal		read_int

	# Use $t0 for comparison
	slt		$t0, $0, $v0
	beq		$t0, $0, main_compare

	# Use $t0 to store read_int output
	add		$t0, $0, $v0

	jal		node_alloc
	sw		$t0, 0($v0)
	sw		$v0, 4($s1)
	add		$s1, $0, $v0

	j		main_loop

main_compare:
	jal		read_int

	# Use $t0 for comparison
	slt		$t0, $0, $v0
	beq		$t0, $0, exit

	# Use $t0 to store read_int output
	add		$s1, $0, $v0
	add		$s2, $0, $s0

	jal		search_list

exit:
	addi	$v0, $0, 10
	syscall
