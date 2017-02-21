	.data
	.align 2

a:				.space 32

str_prompt:		.asciiz "Give me 8 nums: "
str_space:		.asciiz " "
str_sep:		.asciiz "---------------------\n"
str_nlnl:		.asciiz "\n\n"

	.text
	.globl main
	.globl getnum
	.globl putnum

# $10: 
# $11: Pointer to a
# $12: Index for a

# Note: `sll` command is shift logical left (to, from, times)

main:
	la		$11, a
	addi	$10, $0, 8

	# Print the prompt
	addi    $2, $0, 4
	la      $4, str_prompt
	syscall

	# Clear the index
	add		$12, $0, $0
	jal		getnum

	# Print the separator
	addi    $2, $0, 4
	la      $4, str_sep
	syscall

	# Clear the index
	add		$12, $0, 7
	jal		putnum
	j		main

getnum:
	# Pointer stuff (construct index*4+address and increment index)
	sll		$8, $12, 2
	add		$8, $8, $11
	addi	$12, $12, 1

	# Read from the OS
	addi	$2, $0, 5
	syscall
	sw		$2, 0($8)

	# Check the index
	bne		$12, $10, getnum
	jr		$31

putnum:
	# Pointer stuff (construct index*4+address and decrement index)
	sll		$8, $12, 2
	add		$8, $8, $11
	addi	$12, $12, -1

	# Print to console
	addi	$2, $0, 1
	lw		$14, 0($8)
	add		$14, $14, $14	# num*2
	add		$4, $14, $14	# (num*2)*2
	add		$4, $14, $4		# num*2 + (num*2)*2
	syscall

	addi    $2, $0, 4
	la      $4, str_space
	syscall

	# Check the index
	bgez	$12, putnum
	addi    $2, $0, 4
	la      $4, str_nlnl
	syscall
	jr		$31
