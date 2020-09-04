SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all: $(OBJS)

test: $(OBJS)
	./input.out 
	./spmv.out 
	./util.out 

$(OBJS):$(SRCS)
	make FUNC=input -f ../Makefile_avx2.mk
	make FUNC=spmv -f ../Makefile_avx2.mk
	make FUNC=util -f ../Makefile_avx2.mk

clean:
	- rm $(OBJS)
