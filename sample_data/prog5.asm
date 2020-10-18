min:
    slt $t0, $a0, $a1
    beq $t0, $0, ELSE
    add $v0, $zero, $a0
    beq $zero, $zero, DONE
ELSE:
    add $v0, $zero, $a1
DONE:   jr $ra
