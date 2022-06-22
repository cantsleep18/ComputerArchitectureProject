    lw  0   1   val1    $1 = val1(1) 
    lw  0   2   val2    $2 = val2(2) 
    lw  0   3   val3    $4 = val3(3) 
    noop 
    noop 
loop beq 1   2   end    if $1 = $2, go to end 
    noop 
    noop 
    noop 
    add 1   1   1       $1(2) = $1 + $1 
    add 3   2   3       $3(5) = $3 + $2 
    beq 0   0   loop 
    noop 
    noop 
    noop 
end halt 
val1 .fill 1 
val2 .fill 2 
val3 .fill 3 
