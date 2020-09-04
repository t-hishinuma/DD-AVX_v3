SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all: $(OBJS)

test: $(OBJS)
	./std.out $(TEST_SIZE)
	./copy.out $(TEST_SIZE)
	./minus.out $(TEST_SIZE)
	./add.out $(TEST_SIZE)
	./sub.out $(TEST_SIZE)
	./mul.out $(TEST_SIZE)
	./div.out $(TEST_SIZE)

$(OBJS):$(SRCS)
	make FUNC=std -f ../Makefile_core.mk
	make FUNC=copy -f ../Makefile_core.mk
	make FUNC=minus -f ../Makefile_core.mk
	make FUNC=add -f ../Makefile_core.mk
	make FUNC=sub -f ../Makefile_core.mk
	make FUNC=mul -f ../Makefile_core.mk
	make FUNC=div -f ../Makefile_core.mk

clean:
	- rm $(OBJS)
