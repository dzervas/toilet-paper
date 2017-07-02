        .data           # init. data memory with the strings needed:
str_n:  .asciiz "n = "
str_s:  .asciiz "       s = "
str_nl: .asciiz "\n"

        .text           # program memory:
        .globl main             # label "main" must be global;
                                # default trap.handler calls main.
        .globl loop             # global symbols can be specified
                                # symbolically as breakpoints.

main:                       # (1) PRINT A PROMPT:
        addi    $2, $0, 4       # system call code for print_string
        la      $4, str_n       # pseudo-instruction: address of string
        syscall                 # print the string from str_n
                            # (2) READ n (MUST be n≥2 --not checked!):
        addi    $2, $0, 5       # system call code for read_int
        syscall                 # read a line containing an integer
        add     $16, $2, $0     # copy returned int from $2 to n
                            # (3) INITIALIZE s and i:
        add     $17, $0, $0     # s=0;
        addi    $18, $0, 1      # i=1;
loop:                       # (4) LOOP starts here
        add     $17, $17, $18   # s=s+i;
        addi    $18, $18, 1     # i=i+1;
        bne     $18, $16, loop  # repeat while (i!=n)
                            #     LOOP ENDS HERE
                            # (5) PRINT THE ANSWER:
        addi    $2, $0, 4       # system call code for print_string
        la      $4, str_s       # pseudo-instruction: address of string
        syscall                 # print the string from str_s
        addi    $2, $0, 1       # system call code for print_int
        add     $4, $17, $0     # copy argument s to $4
        syscall                 # print the integer in $4 (s)
        addi    $2, $0, 4       # system call code for print_string
        la      $4, str_nl      # pseudo-instruction: address of string
        syscall                 # print a new-line
                            # (6) START ALL OVER AGAIN (infinite loop)
        j       main            # unconditionally jump back to main
