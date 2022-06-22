	lw  0   1   five    $1 = 5 
	lw  0   2   five	$2 = 5 
	lw  0   3   one	    $3 = 1 
    noop 
    noop 
	nor 1   2    4	    $4 = 5 nor 5 
    noop 
    noop 
    noop 
	add 4   3    4	    $4 = reverse of $1 (2's complement)
    halt 
five	.fill 5 
one	.fill 1 
