# generic makefile

# the module names
MODULES = main.cpp libgraph.cpp iohandler.cpp

LIB = -Llib -lopenbgi -lgdi32
INCLUDE = -Ilib

MODE = debug
# release or debug

ifeq ($(MODE), release)
FLAGS += -O2
else
FLAGS += -O0 -g
endif

# Everything after this is generic, no need to edit

OBJS := ${MODULES:%.cpp=bin/%.o}

.PHONY: all run clean
  
all: $(OBJS)
	g++ -o bin/main $(OBJS) $(LIB)

run:
	bin/main
	
clean:
	rm -f bin/main bin/*.o

bin/%.o : src/%.cpp 
	g++ -c $< -o $@ $(FLAGS) $(INCLUDE)

