# Define the compiler and flags
EMCC = emcc
CFLAGS = -O3 -s WASM=1 -s 

EMCC_OPT+=-s MODULARIZE=1
EMCC_OPT+=-s SINGLE_FILE=1
EMCC_OPT+=-lembind
EMCC_OPT+=-fno-threadsafe-statics -fno-stack-protector
EMCC_OPT+=-s INITIAL_MEMORY=64MB -s MAXIMUM_MEMORY=4GB -s ALLOW_MEMORY_GROWTH
EMCC_OPT+=-s EXPORTED_RUNTIME_METHODS=stringToUTF8,lengthBytesUTF8,UTF8ToString,stringToNewUTF8,addFunction
EMCC_OPT+=-s RESERVED_FUNCTION_POINTERS=100000
EMCC_OPT+=-s WASM_BIGINT
EMCC_OPT+=-s ASYNCIFY
# Define the source files and target
KECCAKDIR = ../3rdparty/keccak
THIRDPARTYDIR = ../3rdparty
SRCDIR = ../src
WEBASSEMBLY_SRCDIR = ./src

INC = -I../include -I../3rdparty/keccak  -I../3rdparty -I../proto -I../proto -I ./include

LIBDIR = ../web_assembly/lib 
SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*.cc $(KECCAKDIR)/*.c $(WEBASSEMBLY_SRCDIR)/*.cpp))
TARGET = merkle_patricia_trie.js

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SOURCES)
	$(EMCC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(EMCC_OPT) $(INC) -L$(LIBDIR) -lprotobuf

# Clean rule
clean:
	rm -f $(TARGET) $(TARGET).wasm $(TARGET).js $(TARGET).html

.PHONY: all clean
