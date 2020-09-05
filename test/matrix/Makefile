SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all:
	make FUNC=input -f ../Makefile_core.mk
	make FUNC=spmv -f ../Makefile_core.mk
	make FUNC=util -f ../Makefile_core.mk

test:
	./input.out 
	./util.out 
	./spmv.out test.mtx

clean:
	- rm $(OBJS)
