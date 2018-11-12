OS := $(shell uname)

$(info $(OS))

G_FLAGZ= -Wall -g -fPIC

ifeq ($(OS), Darwin)
    FLAGZ=$(G_FLAGZ) -ldl -fPIC
else
    FLAGZ=$(G_FLAGZ) -ldl -fPIC
endif

EXEC = cola.out
SOURCES := $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_NO_MAIN := $(filter-out src/main.o,$(OBJECTS))

$(info $(OBJECTS_NO_MAIN))

$(EXEC): $(OBJECTS)
	gcc $(OBJECTS) $(FLAGZ) -o $(EXEC) -fPIC

%.o: %.c includes/%.h
	gcc -c $(G_FLAGZ) $< -o $@ -fPIC

liblex.so: $(OBJECTS_NO_MAIN)

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
	-rm src/*/*.o
	-rm src/*/*/*.o
