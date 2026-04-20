CC ?= cc
BASE_CFLAGS := -Wall -Wextra -Werror -std=c11
CFLAGS ?= $(BASE_CFLAGS)
CPPFLAGS ?= -I.
LDFLAGS ?=
LDLIBS ?= -lcrypto

BUILD_MODE ?= debug

ifeq ($(BUILD_MODE),release)
OPTFLAGS ?= -O2
else ifeq ($(BUILD_MODE),debug)
OPTFLAGS ?=
else
$(error BUILD_MODE must be either 'debug' or 'release')
endif

SRC := src/main.c
BUILD_DIR := build
TARGET := $(BUILD_DIR)/main
OBJ := $(BUILD_DIR)/main.o

.PHONY: all debug release clean

all: $(TARGET)

debug:
	$(MAKE) BUILD_MODE=debug $(TARGET)

release:
	$(MAKE) BUILD_MODE=release $(TARGET)

$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@

$(BUILD_DIR)/main.o: $(SRC) include/main.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf build $(TARGET)
