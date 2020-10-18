gcd:
    beq $a0, $a1, L2        
    slt $v0, $a1, $a0       
    bne $v0, $zero, L1      
    subu $a1, $a1, $a0      
    beq $zero, $zero, gcd   
L1:
    subu $a0, $a0, $a1      
    beq $zero, $zero, gcd   
L2:
    add $v0, $zero, $a0     
    jr $ra                  
