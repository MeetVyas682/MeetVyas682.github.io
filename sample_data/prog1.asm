ELSE:
    add $v0, $zero, $a0
DONE:
    jr $ra
max:
    slt $t0, $a0, $a1
    beq $t0, $zero, ELSE
    add $v0, $zero, $a1
    beq $zero, $zero, DONE

