#Following is the C code for the assembly code
#int fact(int n) {
#if (n < 1) return 1;
#else return (n * fact(n - 1));
#}

#assembly code
fact:
    addi $sp, $sp, -8   # allocate 2 words on stack
    sw $ra, 4($sp)      # save return address
    sw $a0, 0($sp)      # and n
    slti $t0, $a0, 1    # n < 1?
    beq $t0, $zero, else   # Go to else
    ori $v0, $zero, 1   # Yes,return 1
    addi $sp, $sp, 8   # Pop 2 words from stack
    jr $ra              # return
else:
    addi $a0, $a0, -1  # compute n-1
    jal fact            # recurse (result in $v0)
    lw $a0, 0($sp)      # Restore n and
    lw $ra, 4($sp)      # return address
    mult $a0, $v0       # Compute n * fact(n-1)
    mfho $v0            # $v0 = n*fact(n-1)
    addi $sp, $sp, 8   # Pop 2 words from stack
    jr $ra              # return
