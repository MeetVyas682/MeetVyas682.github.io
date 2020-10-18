swap:
    sll $v0, $a1, 2    
    add $v0, $a0, $v0   
    lw $t0, 0($v0)      
    lw $s0, 4($v0)      
    sw $s0, 0($v0)      
    sw $t0, 4($v0)      
    jr $ra  