    .module crt0
    .globl  _main

    .area   _HEADER (ABS)
    ;; Reset vector
    .org    0
    jp  init

    .org    0x08
    ei
    reti
    .org    0x10
    ei
    reti
    .org    0x18
    ei
    reti
    .org    0x20
    ei
    reti
    .org    0x28
    ei
    reti
    .org    0x30
    ei
    reti
    
    ;;
    ;; CyBorg IM1 IRQ vector
    ;;
    .org    0x38
    push    af
    push    bc
    push    de
    push    hl
    push    iy
    call    _IM1_IRQ_ISR
    pop iy
    pop hl
    pop de
    pop bc
    pop af
    ei
    reti

    .org    0x100
init:
    ;; Set stack pointer directly above top of memory.
    ld  sp,#0x0000

    ;; Initialise global variables
    call    gsinit
    call    _main
    jp  _exit

    ;; Ordering of segments for the linker.
    .area   _HOME
    .area   _CODE
    .area   _INITIALIZER
    .area   _GSINIT
    .area   _GSFINAL

    .area   _DATA
    .area   _INITIALIZED
    .area   _BSEG
    .area   _BSS
    .area   _HEAP

    .area   _CODE
__clock::
    ld  a,#2
    rst 0x08
    ret

_exit::
    ;; Exit - special code to the emulator
    ld  a,#0
    rst 0x08
1$:
    halt
    jr  1$

    .area   _GSINIT
gsinit::

    ; Default-initialized global variables.
    ld      bc, #l__DATA
    ld      a, b
    or      a, c
    jr      Z, zeroed_data
    ld      hl, #s__DATA
    ld      (hl), #0x00
    dec     bc
    ld      a, b
    or      a, c
    jr      Z, zeroed_data
    ld      e, l
    ld      d, h
    inc     de
    ldir
zeroed_data:

    ; Explicitly initialized global variables.
    ld  bc, #l__INITIALIZER
    ld  a, b
    or  a, c
    jr  Z, gsinit_next
    ld  de, #s__INITIALIZED
    ld  hl, #s__INITIALIZER
    ldir

gsinit_next:

    .area   _GSFINAL
    ret
