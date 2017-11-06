TARGET := ./bin/sfsasm
TESTTARGET := ./test/sfsasm-test
LIBS := 
CC := gcc
CFLAGS := -g -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion
INC := -I./include
TESTINC := -I./test/include

.PHONY: all default test clean

all: default test
default: $(TARGET)
test: $(TESTTARGET)

SOURCES := $(shell find ./src -type f -name '*.c')
OBJECTS := $(patsubst ./src/%, ./build/%, $(SOURCES:.c=.o))
HEADERS := $(wildcard ./include/*.h)

TESTSOURCES := $(shell find ./test -type f -name '*.c')
TESTOBJECTS := $(patsubst ./test/%, ./build/test/%, $(TESTSOURCES:.c=.o))
TESTHEADERS := $(wildcard ./test/include/*.h)

./build/%.o: ./src/%.c $(HEADERS)
	@mkdir -p ./build
	$(CC) $(ARGCFLAGS) $(CFLAGS) $(INC) -c $< -o $@

./build/test/%.o: ./test/%.c $(HEADERS) $(TESTHEADERS)
	@mkdir -p ./build/test
	$(CC) $(ARGCFLAGS) $(CFLAGS) $(INC) $(TESTINC) -c $< -o $@

.PRECIOUS: $(TARGET) $(TESTTARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	@mkdir -p ./bin
	$(CC) $^ $(ARGCFLAGS) $(CFLAGS) $(LIBS) -o $@

$(TESTTARGET): $(filter-out ./build/main.o, $(OBJECTS)) $(TESTOBJECTS)
	$(CC) $^ $(ARGCFLAGS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -rf ./build
	-rm -f $(TARGET)
	-rm -f $(TESTTARGET)
