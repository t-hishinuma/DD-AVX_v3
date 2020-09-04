SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all: $(OBJS)

test: $(OBJS)
	./scalar.out $(TEST_SIZE)
	./vector_element.out $(TEST_SIZE)

$(OBJS):$(SRCS)
	make FUNC=scalar -f ../Makefile_avx2.mk
	make FUNC=vector_element -f ../Makefile_avx2.mk

clean:
	rm $(OBJS)
