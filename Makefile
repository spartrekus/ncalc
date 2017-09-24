
all:
	  gcc -lm tinyexpr.c -lncurses ncalc.c     -o ncalc 

run:
	  gcc -lm tinyexpr.c -lncurses ncalc.c     -o ncalc  ; ./ncalc 


ed:
	  vim ncalc.c 



