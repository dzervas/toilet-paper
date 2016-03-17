	.text              # program memory:
	.globl main            # label "main" must be global ;
	# bootstrap trap.handler calls main.

main:
	# registers:  $16: i ; $17: j;
	addi   $16, $0,  10    # init. i=10 ; ($0==0 always)
	addi   $17, $0,  64    # init. j=64 ; (64 decimal = 40 hex)
	add    $18, $16, $17   # $18 <- i+j = 74 dec = 4a hex
	add    $18, $18, $18   # $18 <- 74+74=148 dec = 94 hex
	add    $18, $18, $17   # $18 <-148+64=212 dec = d4 hex
	addi   $17, $17, -1    # j <- j-1 = 63 dec = 3f hex
	sub    $17, $17, $16   # j <- j-i = 53 dec = 35 hex
	j      main            # jump back to main (infinite loop)
	
