SRCS =$(notdir $(wildcard ./src/*.cpp))
SRCS+=$(notdir $(wildcard ./src/goma/*.cpp))

# vpath %.cpp ./src/
# vpath %.cpp ./src/goma

OBJDIR=src/obj
OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

all: $(OBJS)
# 	echo $(SRCS)
# 	echo $(OBJS)

$(OBJDIR)/%.o: %.cpp
	g++ -I include/ -o $@ -c $<
