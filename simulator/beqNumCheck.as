    lw 0 1 val1 reg1 = 3 
    lw 0 2 val2 reg2 = 4 
    lw 0 3 n reg3 = 7 
    add 1 2 4 reg4 = 3+4 
    beq 3 4 pass reg3 == reg4 go to pass 
    noop 
    sw 0 4 result if reg3 != reg4 then result = 7 
    halt 
pass    add 2 4 4 reg4 = 7 + 4 = 11 
    sw 0 4 result if reg3 == reg4 then result = 11 
    halt 
val1    .fill 3 
val2    .fill 4 
n   .fill 7 
result .fill 10 
