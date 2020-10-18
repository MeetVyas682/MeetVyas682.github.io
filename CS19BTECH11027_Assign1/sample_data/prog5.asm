#Following is the C code for the assembly code
#void threshold(int img[], int size, int thresh)
#{
#    for(int i=0;i<size;i++)
#    {
#        if(img[i]>thresh)
#            img[i] = 255;
#        else
#            img[i] = 0;
#    }
#}

#assembly code
threshold:
    addi $s0, $zero, 0      #i=0
    addi $s2, $zero, 255    #s2 = 255
loop:
    slt $t0, $s0, $a1       #set to 1 if (i<size)
    beq $t0, $zero, loopend #exit if equals 0
    add $t0, $a0, $s0       #address = img[0] + i
    lw $t1, 0($t0)          # t1 = img[i]
    slt $t2, $s1, $t1       #t2 = 1 if thresh <img[i]
    beq $t2, $zero, else    #branch to else
    sw $s2, 0($t0)          #img[i] = 255
    j elseend               #jump to elseend
else;
    sw $zero, 0($t0)        #img[i] = 0
elseend:
    addi $s0, $s0, 1        #i++
    j loop                  #jump to loop
loopend:
    jr $ra                  #return
