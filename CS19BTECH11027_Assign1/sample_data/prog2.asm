#Following is the C code for the assembly code
#int amrstrong(int a)
#{
#   int b = a;
#   int c = 0;
#   int d = 0;
#   int ans  = 0;
#   while (b!=0) {
#       c = b%10;
#       b = b/10;
#       d = d + c*c*c;
#   }
#   if (d == a) ans = 1;
#   return a;
#}
# a is stored in $a0 and b in $s0, c in $s1, d in $s2, ans in $s3, t0 for 10, t1 for c*c

#assembly code

amrstrong:
    addi $sp, $sp, -24  # adjust stack to make room for 6 items
    sw $t1, 20($sp)     # save register $t1 for use afterwards
    sw $t0, 16($sp)     # save register $t0 for use afterwards
    sw $s3, 12($sp)     # save register $s3 for use afterwards
    sw $s2, 8($sp)      # save register $s2 for use afterwards
    sw $s1, 4($sp)      # save register $s1 for use afterwards
    sw $s0, 0($sp)      # save register $s0 for use afterwards

    add $s0, $zero, $a0         # b = a
    addi $s1, $zero, 0          # c = 0
    addi $s2, $zero, 0          # d = 0
    addi $s3, $zero, 0          # ans = 0
    ori $t0, $zero, 10          # load constant
    beq $zero, $zero, check     #branch to check
loop:
    div $s0, $t0        #hi = b%10 and lo = b/10
    mfhi $s1            #c = b%10
    mflo $s0            #b = b/10
    mult $s1, $s1       #hi = c*c and lo = c*c
    mfhi $t1            #storing value of c*c in t1
    mult $t1, $s1       #hi = c*c*c and lo = c*c*c
    mfhi $t1            #storing value of c*c*c in t1
    add $s2, $s2, $t1   # d = d + c*c*c
    beq $zero, $zero, check     # branch to check
check:
    bne $s0, $zero, loop   # b!=0 then branch to loop
    beq $zero, $zero, end   # branch to end

end:
    bne $s2, $a0, return   # if (d!=a) then branch to return
    addi $s3, $zero, 1      # add = 1
return:
    add $v0, $zero, $s3  #return a
    jr $ra               #return to caller
