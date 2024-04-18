# select version if necessary
#VER=32
#VER=64

TEST=big_num_test
TARGET=big_num
TARGET_LL=big_num_ll
LIBNAME=libbignum

CFLAGS += $(shell gcc -v 2>&1 | grep enable-default-pie > /dev/null && echo \-no\-pie)
CFLAGS += -g -std=c99

ifndef VER
  VER=32
  ifeq ($(shell uname -m),x86_64)
    VER=64
  endif
endif

ifeq ($(VER),32)
  NASMFLAGS=-f elf
  CFLAGS+=-m32
  LDFLAGS+=
else
ifeq ($(VER),64)
  NASMFLAGS=-f elf64
  CFLAGS+=
  LDFLAGS+=
else
  $(error Unknown value of VER)
endif
endif

LIBFILE=$(LIBNAME)$(VER).a
NASMFLAGS+=-g
CFLAGS+=-g 
LDFLAGS+=$(LIBFILE)

all: $(TARGET)

%.o: %.asm
	nasm $(NASMFLAGS) $<

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

$(TARGET_LL): $(TARGET_LL).o
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

test: $(TEST)

$(TEST): $(TEST).o
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

lib: $(LIBFILE)

$(LIBFILE): lib_asm.o lib_c.o
	rm -f $@
	ar r $@ $^
	rm -f $^

clean:
	rm -rf $(TARGET) $(TARGET_LL) $(TEST) *.o

cleanall: clean
	rm -rf *.a

