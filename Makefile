# generic makefile

CC = gcc
EXT = c

# modules
MODULES = $(wildcard src/*.$(EXT))

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

# Everything after this is generic, no need to edit

OBJS := ${MODULES:src/%.$(EXT)=bin/%.o}

.PHONY: all run clean
  
all: $(OBJS)
	$(CC) -o bin/main $(OBJS) $(LIB)

run:
	bin/main
	
clean:
	rm -f bin/main bin/*.o

bin/%.o : src/%.$(EXT)
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDE)

