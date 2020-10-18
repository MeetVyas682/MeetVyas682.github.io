# HLL Code
# set N to the smallest odd no less than N
#    if ( N%2 == 0 ) N++;



# MIPS Code
    
lw    $t0, 4($gp)         # fetch N
ori   $t0, $t0, 1         # turn on low order bit
sw    $t0, 4($gp)         # store result in N
