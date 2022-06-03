    lw 0 1 val1 reg1 = 5 
    lw 0 2 val2 reg2 = 8 
    lw 0 4 jmpAdd reg4 = addr of Swap 
    jalr 4 7 store addr pc+1 in reg7 go to 4 
    halt 
    noop 
swap    add 1 0 3 tmp reg 3 
    sw 0 2 val1 value of reg2 in memory addr val1 
    sw 0 3 val2 value of reg3 in memory addr val2 
    halt 
val1 .fill 5 
val2 .fill 8 
jmpAdd .fill swap
