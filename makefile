
# prompt> make
# builds everything and links in test program test_rb
#
# prompt> make mem_check
# Rebuilds everything using dmalloc and does memory testing.
# Only works if you have dmalloc installed (see http://dmalloc.com).

SRCS = bbst.cpp red_black_tree.cpp stack.cpp 

HDRS = red_black_tree.h stack.h

OBJS = stack.o red_black_tree.o bbst.o 

CC = g++

CFLAGS = -g -Wall -pedantic

PROGRAM = bbst 


all: $(PROGRAM)

$(PROGRAM): 	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) $(DMALLOC_LIB)



bbst.o:	bbst.cpp red_black_tree.cpp stack.cpp red_black_tree.h stack.h

red_black_tree.o:	red_black_tree.h red_black_tree.cpp stack.cpp stack.h


clean:			
	rm -f *.o *~ $(PROGRAM)






