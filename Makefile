# generic makefile

# the module names
MODULES = main.c iohandler.c libgraph.c button.c point.c rect.c line.c polygon.c

LIB = -Llib -lopenbgi -lgdi32
INCLUDE = -Ilib

MODE = debug
# release or debug

FLAGS = -std=c99

ifeq ($(MODE), release)
FLAGS += -O2
else
FLAGS += -O0 -g
endif

CC = gcc
EXT = c

# Everything after this is generic, no need to edit

OBJS := ${MODULES:%.$(EXT)=bin/%.o}

.PHONY: all run clean
  
all: $(OBJS)
	$(CC) -o bin/main $(OBJS) $(LIB)

run:
	bin/main
	
clean:
	rm -f bin/main bin/*.o

bin/%.o : src/%.$(EXT)
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDE)

