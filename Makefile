PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SRC = $(PROJECT_ROOT)src/
INC = $(PROJECT_ROOT)inc/

CXX = /usr/local/CrossPack-AVR/bin/avr-gcc
CC = /usr/local/CrossPack-AVR/bin/avr-gcc

OBJCOPY = /usr/local/CrossPack-AVR/bin/avr-objcopy

MODULES = $(SRC)ioport/

INCLUDE_DIRS = $(MODULES) $(INC)
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)
ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -Os
else
	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

CFLAGS += -mmcu=at90can128

C_DEFINES = GCC_MEGA_AVR
C_DEFINE_PARAMS = $(foreach d, $(C_DEFINES), -D$d)

all:	at90.hex

at90.hex: at90.elf
	$(OBJCOPY) -O ihex -j .text -j .data at90.elf at90.hex

at90.elf: *.o
	$(CC) -mmcu=at90can128 $^ -o $@

*.o: $(wildcard $(SRC)*.c) $(wildcard $(MODULES)*.c) $(SRC)portable/gcc/atmega323/port.c $(SRC)portable/mem_man/heap_1.c
	$(CC) -c $(CFLAGS) $(C_DEFINE_PARAMS) $(INC_PARAMS) $^

clean:
	rm -fr *.hex *.elf *.o
