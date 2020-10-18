# simple Swap code in MIPS


swap:
    sll $v0, $a1, 2     # $v0 = k<<2
    add $v0, $a0, $v0   # adding 4*k to v
    lw $t0, 0($v0)      # $v0 = memory[$s0+0]
    lw $s0, 4($v0)      # $s0 = memory[$s0+4]
    sw $s0, 0($v0)      # memory[$v0] = $s0
    sw $t0, 4($v0)      # memory[$v0 + 4] = $t0
    jr $ra              # return 
