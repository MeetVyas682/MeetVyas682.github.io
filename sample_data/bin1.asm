add $v0, $zero, $a0
jr $ra
slt $t0, $a0, $a1
jal Function at 26-bit address: 01000000000000000000000000
add $v0, $zero, $a1
beq $zero, $zero, Function at 26-bit address: 0000000000000001
