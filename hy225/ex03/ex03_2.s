	.data
str_xyz:	.asciiz "xyz"
str_a:		.asciiz "a"
str_z:		.asciiz "z"
str_A:		.asciiz "A"
str_Z:		.asciiz "Z"
str_0:		.asciiz "0"
str_1:		.asciiz "1"
str_9:		.asciiz "9"
	.text
	.globl main

main:
	la      $17, str_xyz
	la      $10, str_a
	la      $11, str_z
	la      $12, str_A
	la      $13, str_Z
	la      $14, str_0
	la      $15, str_1
	la      $16, str_9

	la      $4, str_xyz
	addi	$2, $0, 1
	syscall
