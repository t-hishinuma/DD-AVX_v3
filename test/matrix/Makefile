SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all: $(OBJS)

test: $(OBJS)
	./input.out 
	./util.out 
	./spmv.out test.mtx

$(OBJS):$(SRCS)
	make FUNC=input -f ../Makefile_core.mk
	make FUNC=spmv -f ../Makefile_core.mk
	make FUNC=util -f ../Makefile_core.mk

clean:
	- rm $(OBJS)
