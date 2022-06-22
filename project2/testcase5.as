    lw  0   1   val1    $1 = val1(1) / Example for Data Hazard 
    lw  0   2   val2    $2 = val2(2) 
    lw  0   4   val3    $4 = val3(3) 
    add 1   2   3       $3 = $1 + $2 / Since, the result of $1, $2 is not wrote back from line 1, 2, This line has Data Hazard (there is no forwarding in my simulator)
    sw  0   3   val1    val1 - $3(3) / There is Data Hazard between add and sw, too,  I need stalls to solve these problem 
    add 1   4   5       $5 = $1 + $4 
    sw  0   5   val2    val2 - $5(4) / There is Data Hazard between add and sw, too,  I need stalls to solve these problem 
    halt 
val1 .fill 1 
val2 .fill 2 
val3 .fill 3 
