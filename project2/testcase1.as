    lw  0   1   val1    $1 = val1(1) 
    lw  0   2   val2    $2 = val2(2) 
    lw  0   4   val3    $4 = val3(3) 
    noop 
    noop 
    add 1   2   3       $3 = $1 + $2
    noop 
    noop 
    noop 
    sw  0   3   val1    val1 - $3(3) 
    add 1   4   5       $5 = $1 + $4
    noop 
    noop 
    noop 
    sw  0   5   val2    val2 - $5(4)  
    halt 
val1 .fill 1 
val2 .fill 2 
val3 .fill 3 
