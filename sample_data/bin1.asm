beq $a0, $a1, Function at 16-bit address: 0000000000000010
slt $v0, $a1, $a0
bne $v0, $zero, Function at 16-bit address: 0000000000000001
subu $a1, $a1, $a0
beq $zero, $zero, Function at 16-bit address: 0000000000000000
subu $a0, $a0, $a1
beq $zero, $zero, Function at 16-bit address: 0000000000000000
add $v0, $zero, $a0
jr $ra
