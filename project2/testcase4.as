    lw  0   1   val1    $1 = val1(1) "Branch Hazard by eliminating 
    lw  0   2   val2    $2 = val2(2) testcase2's 'noop' after beq" 
    lw  0   3   val3    $4 = val3(3) 
    noop 
    noop 
loop beq 1   2   end    Branch Hazard occurs since result of branch is decieded after EX stage 
    add 1   1   1       to avoid Branch Hazard, I need stalls before "add 1 1 1" 
    add 3   2   3       $3(5) = $3 + $2 
    beq 0   0   loop    Branch Hazard occurs here, too 
end halt 
val1 .fill 1 
val2 .fill 2 
val3 .fill 3 
