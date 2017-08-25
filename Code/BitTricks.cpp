// Tricks to use on bits

// Turn off rightmost bit
x&(x+1)

// Turn on rightmost 0
x|(x+1)

// Turn off trailing 1s 
x&(x+1)

// Turn trailing 0s on
x|(x-1)

// Returns number with 1 at rightmost 1 of x
-x&(x+1)

// Returns a number with a 0 at rightmost 1 of x
-x|(x-1)

// Replaces trailing 0s with ones and everything else with 0(3 // different ways)
-x&(x-1)
-(x|-x)
(x&-x)-1

// Replaces trailing 1s with 0s and everything else with 1
-x|(x+1)

// Issolate right most bit
x&(-x)

// Produce word with 1s in place of trailing zeros and rightmost bit and 0s everywhere else
x^(x-1)

// Produce word with 1s in place of trailing 1s and rightmost zero and 0s everywhere else:
x^(x+1)

// Turn off the right most contiguous string of 1s(2 ways)
(((x|(x-1))+1)&x)
((x&-x)+x)&x




