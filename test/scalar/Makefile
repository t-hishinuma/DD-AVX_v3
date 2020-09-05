SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all: 
	make FUNC=scalar -f ../Makefile_core.mk
	make FUNC=vector_element -f ../Makefile_core.mk

test: 
	./scalar.out 
	./vector_element.out 

clean:
	rm $(OBJS)
