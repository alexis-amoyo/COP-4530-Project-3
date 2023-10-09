CC := g++

CFLAGS := -std=c++11 

SRCS := test_stack1.cpp in2post.cpp

OBJS := ${SRCS:.cpp=.o} test_stack1.o in2post.o

PROGS := ${SRCS:.cpp=} 

.PHONY: all
all: ${PROGS}

test_stack1: test_stack1.o
	${CC} ${CFLAGS} -o $@ $^

in2post: in2post.o
	${CC} ${CFLAGS} -o $@ $^
	
%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} ${OBJS} *.bak *~
