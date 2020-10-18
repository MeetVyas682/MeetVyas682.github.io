# Finding GCD
gcd:
    beq $a0, $a1, L2        # if a==b, go to exit
    slt $v0, $a1, $a0       # if b>a?
    bne $v0, $zero, L1      # yes, goto L1
    subu $a1, $a1, $a0      # subtract b from a (b<a)
    beq $zero, $zero, gcd   # repeat
L1:
    subu $a0, $a0, $a1      # subtract a from b (a<b)
    beq $zero, $zero, gcd   # repeat
L2:
    add $v0, $zero, $a0     # return a
    jr $ra                  # return to caller