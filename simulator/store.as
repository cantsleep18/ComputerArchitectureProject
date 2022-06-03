    lw 0 1 val1 reg1 = 3(val1) 
    lw 0 2 val2 reg2 = 5(val2) 
    sw 0 1 val2 val2 to 3 
    lw 0 3 val2 reg3 = 3(val2) 
    beq 2 3 pass if reg2 != reg3 then goto pass  
    add 2 3 4 result 5+3 = 8 when reg2 == reg3 
    noop 
    halt 
pass    add 1 3 4 result 3+3 = 6 when reg2 != reg3 
    halt 
val1    .fill 3 
val2    .fill 5 
