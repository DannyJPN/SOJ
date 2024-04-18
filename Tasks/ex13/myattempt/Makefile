TARGET=c-main

ARCH=64

ifeq ($(ARCH), 32)
CFLAGS += -m32
endif

CFLAGS += $(shell gcc -v 2>&1 | grep enable-default-pie > /dev/null && echo \-no\-pie)
CFLAGS += -g

all: $(TARGET)

%.o: %.asm
	nasm -g -f elf$(ARCH) $<

clean:
	rm -rf $(TARGET) *.o

$(TARGET): asm-module.o c-main.cpp
	g++ $(CFLAGS) asm-module.o c-main.cpp -o $(TARGET)
