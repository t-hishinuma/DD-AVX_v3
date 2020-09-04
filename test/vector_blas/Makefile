SRCS =$(notdir $(wildcard ./*.cpp))
vpath %.cpp ./
OBJS=$(addprefix ./, $(SRCS:.cpp=.out))

TEST_SIZE?=100

all: $(OBJS)

test: $(OBJS)
	./axpy.out $(TEST_SIZE)
	./axpyz.out $(TEST_SIZE)
	./xpay.out $(TEST_SIZE)
	./scale.out $(TEST_SIZE)
	./dot.out $(TEST_SIZE)
	./nrm2.out $(TEST_SIZE)

$(OBJS):$(SRCS)
	make FUNC=axpy -f ../Makefile_core.mk
	make FUNC=axpyz -f ../Makefile_core.mk
	make FUNC=xpay -f ../Makefile_core.mk
	make FUNC=scale -f ../Makefile_core.mk
	make FUNC=dot -f ../Makefile_core.mk
	make FUNC=nrm2 -f ../Makefile_core.mk


clean:
	- rm $(OBJS)
