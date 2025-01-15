CC=zcc
AS=zcc
TARGET=+embedded
VERBOSITY=-vn
CRT=1

SOURCES=Kernel/kernel.c Common/io.c

PRAGMA_FILE=zpragma.inc

C_OPT_FLAGS=-SO3 --max-allocs-per-node200000

CFLAGS=$(TARGET) $(VERBOSITY) -c $(C_OPT_FLAGS) -compiler sdcc -clib=sdcc_iy -pragma-include:$(PRAGMA_FILE)
LDFLAGS=$(TARGET) $(VERBOSITY) -clib=sdcc_iy -pragma-include:$(PRAGMA_FILE)
ASFLAGS=$(TARGET) $(VERBOSITY) -c

EXEC=kernel.bin
EXEC_OUTPUT=kernel

OBJECTS=$(patsubst %.c,%.o, $(SOURCES))

%.o: %.c $(PRAGMA_FILE)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

all : $(EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) $(LDFLAGS) -startup=$(CRT) $(OBJECTS) -o $(EXEC_OUTPUT) -create-app

.PHONY: clean

clean:
	rm -rf Kernel/*.o
	rm -rf Common/*.o
