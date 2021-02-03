# Source directory
SRC_DIR = src
# Bin directory
BIN_DIR = bin
# Target executable
TARGET  = shutdown


# post processing directory names:
# removing trailing slashes if necessary
SRC_DIR := $(SRC_DIR:%/=%)
BIN_DIR := $(BIN_DIR:%/=%)


# Makefile
MAKEFILE = $(lastword $(MAKEFILE_LIST))
# List of all cpp-files.
SRCS = $(wildcard ${SRC_DIR}/*.cpp)
# List of resulting o-files in bin directory.
OBJS = $(patsubst ${SRC_DIR}/%.cpp, ${BIN_DIR}/%.o, ${SRCS})

# Release-independent Compiler & (Linker-)Flags
CC     = g++
CFLAGS = -Wall -c
LFLAGS = -lbcm2835

# Create bin dir
$(shell mkdir -p ${BIN_DIR})


# Target definitions
.PHONY: all release depend clean

# default compilation is debug
all: debug

# debug configuration
debug: CFLAGS += -DDEBUG -g
debug: $(TARGET)

# release configuration
release: CFLAGS += -fdata-sections -ffunction-sections
release: LFLAGS += -Wl,--gc-sections
release: $(TARGET)

# Link object files to executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)
	@echo "$(TARGET) built!"

# Compile sources to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean all build files
clean:
	-rm -rf $(TARGET) $(TARGET)*.stackdump $(BIN_DIR) 

# Add header (*.h) file dependencies
depend: $(SRCS)
	@makedepend -Y -I$(SRC_DIR) $(SRCS) 2> /dev/null
	@sed -i 's|^$(SRC_DIR)/|$(BIN_DIR)/|g' $(MAKEFILE)
	@echo Updated dependencies within $(MAKEFILE).


# DO NOT DELETE

bin/IPin.o: src/IPin.h src/debug.h
bin/PullUpPin.o: src/PullUpPin.h src/InputPin.h src/IPin.h src/APin.h
bin/PullUpPin.o: src/debug.h
bin/APin.o: src/APin.h src/IPin.h src/debug.h
bin/InputPin.o: src/InputPin.h src/IPin.h src/APin.h src/debug.h
bin/shutdown.o: src/debug.h src/Bcm2835.h src/IPin.h src/PullUpPin.h
bin/shutdown.o: src/InputPin.h src/APin.h
bin/Bcm2835.o: src/Bcm2835.h src/IPin.h src/PullUpPin.h src/InputPin.h
bin/Bcm2835.o: src/APin.h src/debug.h
