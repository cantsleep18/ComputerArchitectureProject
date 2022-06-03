    lw 0 1 val1    start point(i) 
    lw 0 2 val2    end point 
    lw 0 4 val1     plus one 
loop    beq 1 2 end 
    add 1 3 3      add to result 
    add 1 4 1      add 1 to is 
    beq 0 0 loop 
end     sw 0 3 result 
    halt 
val1    .fill 1 
val2    .fill 5 
result  .fill 0 
