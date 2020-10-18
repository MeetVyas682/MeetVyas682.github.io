# Random Function written in MIPS

LCD:
    addi $sp, $sp, -12
    sw $t0, 8($sp)
    sw $s1, 4($sp)
    sw $s0, 0($sp)
    addi $s0, $zero, 18
    addi $s1, $zero, -17
    beq $a0, $a1, L2        
    slt $v0, $a1, $a0       
    bne $v0, $zero, L1      
    subu $a1, $a1, $a0      
    beq $zero, $zero, LCD   
L1:
    subu $a0, $a0, $a1      
    beq $zero, $zero, LCD   
L2:
    mult $s0, $s1
    mfhi $t0
    div $t0, $a0
    mflo $v0     
    jr $ra       