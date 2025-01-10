ASM_BUILD := sdasz80
ASM_OPTS := -p -l -o -s -g -ff build/cyos_crt0.rel
ASM_SRC := Kernel/crt0.S
CC := sdcc
CC_OPTS := -mz80 --no-std-crt0 cyos_crt0.rel
SREC := srec_cat
SREC_OPTS := -disable-sequence-warnings cyos.hex -Intel -o cyos.hex -Intel

build:
	mkdir build
	${ASM_BUILD} ${ASM_OPTS} ${ASM_SRC}

clean:
	-rm -rf build
