addi $sp, $sp, -12
sw $t0, 8($sp)
sw $s1, 4($sp)
sw $s0, 0($sp)
addi $s0, $zero, 18
addi $s1, $zero, -17
beq $a0, $a1, Function at 16-bit address: 0000000000000010
slt $v0, $a1, $a0
bne $v0, $zero, Function at 16-bit address: 0000000000000001
subu $a1, $a1, $a0
beq $zero, $zero, Function at 16-bit address: 0000000000000000
subu $a0, $a0, $a1
beq $zero, $zero, Function at 16-bit address: 0000000000000000
mult $s0, $s1
mfhi $t0
div $t0, $a0
mflo $v0
jr $ra
