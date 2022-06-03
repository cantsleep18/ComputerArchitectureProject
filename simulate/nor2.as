    lw 0 1 val1 reg1 = 5 
    lw 0 3 one reg3 = 1 
    noop 
    nor 0 1 2 not (reg1 or 0) 
    add 3 2 2 to reverse reg3+1 
    sw 0 2 val1 store -5 
    halt 
val1    .fill 5 
one     .fill 1 
