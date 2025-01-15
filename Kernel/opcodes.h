#ifndef _OPCODES_H
#define _OPCODES_H
// These are taken directly from https://github.com/cyrusbuilt/CyBorg-Northbridge/blob/main/include/opcodes.h

/**
 * I/O Write OpCodes. All OpCodes except OP_IO_WR_WRTSCT (write sector)
 * only exchange a single byte. WRTSCT can exchange 512 bytes.
 */

// TODO Possible OpCodes to suspend the main CPU to allow add-on cards with
// other CPUs on them to run? Or allow switching back-and-forth?

/**
 * @brief Write USER LED. If Bit 7 (PIN_D0) is HIGH, then LED is ON.
 */
#define OP_IO_WR_USR_LED 0x00

/**
 * @brief Write Serial TX. Byte value is considered an ASCII char and is
 * sent to serial.
 */
#define OP_IO_WR_SER_TX 0x01

/**
 * @brief Writes the data byte value to GPIOA on the MCP23017.
 */
#define OP_IO_WR_GPIOA 0x03

/**
 * @brief Writes the data byte value to GPIOB on the MCP23017.
 */
#define OP_IO_WR_GPIOB 0x04

/**
 * @brief Writes the data byte value to IODIRA on the MCP23017.
 */
#define OP_IO_WR_IODIRA 0x05

/**
 * @brief Writes the data byte value to IODIRB on the MCP23017.
 */
#define OP_IO_WR_IODIRB 0x06

/**
 * @brief Writes the data byte value to GPPUA on the MCP23017.
 */
#define OP_IO_WR_GPPUA 0x07

/**
 * @brief Writes the data byte value to GPPUB on the MCP23017.
 */
#define OP_IO_WR_GPPUB 0x08

/**
 * @brief DISK EMULATION. Select the emulated disk number (binary). 100 disks
 * are supported [0..99]. Opens the "disk file" corresponding to the  selected
 * disk number, doing some checks. A "disk file" is a binary file that emulates
 * a disk using a LBA-like logical sector number. Every "disk file" must have a
 * dimension of 83888608 bytes, corresponding to 16384 LBA-like logical sectors
 * (each sector is 512 bytes long), corresponding to 512 tracks of 32 sectors
 * each (see OP_IO_WR_SELTRK and OP_IO_WR_SELSCT OpCodes). Errors are stored in
 * errDisk (see IO_OP_RD_ERRDSK OpCode).
 * 
 * "Disk file" filename convention:
 * Every "disk file" must follow the syntax "DSxNyy" where:
 *   "x" is the "disk set" and must be in the [0..99] range (always one numeric
 *   ASCII character).
 * 
 *   "yy" is the "disk number" and must be in the [0..99] range (always two
 *   numeric ASCII characters).
 * 
 * NOTE: The maximum disks number *may* be lower due to the limitations of the
 * OS being used (e.g. CP/M 2.2 supports a max of 16 disks).
 * NOTE: A SELDSK operation *MUST* be executed *prior* to using a WRTSCT or
 * RDSCT operation.
 */
#define OP_IO_WR_SELDSK 0x09

/**
 * @brief DISK EMULATION. Select the emulated track number (word split into a
 * 2-byte sequence: DATA 0 and DATA 1). Stores the selected track number into
 * trackSel for "disk file" access. The SELTRK and SELSCT operations convert
 * the legacy track/sector address into a LBA-like logical sector number used
 * to set the logical sector address inside the "disk file". A control is
 * performed on both current sector and track number for valid values.
 * Errors are stored in diskErr (see OP_IO_RD_ERRDSK OpCode).
 * 
 * NOTE: Allowed track numbers are in the range [0..511] (512 tracks).
 * NOTE: Before a WRTSCT or RDSECT operation, a SELSCT or SELTRK operation
 * *MUST* be performed.
 */
#define OP_IO_WR_SELTRK 0x0A

/**
 * @brief DISK EMULATION. Select the emulated sector number (binary). Stores
 * the selected sector number into sectSel for "disk file" access. A control
 * is performed on both current sector and track number for valid values.
 * Errors are stored in diskErr (see OP_IO_RD_ERRDSK OpCode).
 * 
 * NOTE: Allowed sector numbers are in the range [0..31] (32 sectors).
 * NOTE: Before a WRTSCT or RDSECT operation, a SELSCT or SELTRK operation
 * *MUST* be performed *first*.
 */
#define OP_IO_WR_SELSCT 0x0B

/**
 * @brief DISK EMULATION. Write 512 data bytes sequentially into the current
 * emulated disk/track/sector. Writes the current sector (512 bytes) of the
 * current track, one data byte per each call. All the 512 calls must always
 * be performed sequentially to have a WRTSCT operation complete successfully.
 * If an error occurs during the WRTSCT operation, all subsequent write
 * operations will be ignored and the write finalization will not be performed.
 * 
 * If an error occurs calling any DISK EMULATION OpCode (SDMNT excluded)
 * immediately prior the WRTSCT OpCode call, then all data writes will be
 * ignored and the WRTSCT operation will not be performed. Errors are stored in
 * diskErr (see OP_IO_RD_ERRDSK OpCode).
 * 
 * NOTE: A SELTRK or SELSCT *MUST* be performed *prior* to WRTSCT.
 * NOTE: Remember to open the right "disk file" at first using SELDSK.
 * NOTE: The write finalization on SD "disk file" is executed only on the 512th
 * data byte exchange, so be sure that exactly 512 data bytes are exchanged.
 */
#define OP_IO_WR_WRTSCT 0x0C

/**
 * @brief BANKED RAM. Set the memory bank to use (binary). Set 32KB RAM bank
 * for the lower half of the Z80 address space (from 0x0000 to 0x7FFF). The
 * upper half (from 0x8000 to 0xFFFF) is the common fixed bank. Allowed bank
 * numbers are in the range [0..2].
 * 
 * Please note that there three kinds of bank numbers (see schematic):
 * 1) The "OS Bank" number is the bank number managed (known) by the OS.
 * 2) The "Logical Bank" number is the bank seen by the Atmega32a (through
 * BANK1 and BANK0 address lines).
 * 3) The "Physical Bank" number is the *real* bank address inside the RAM
 * chip (RAM_A16 and RAM_A15 address lines).
 * 
 * The following tables show the relationships:
 * 
 *   OS BANK | Logical Bank |  Z80 Address Bus   |   Physical Bank   | Notes
 *   number  | BANK1 BANK0  |       A15          |  RAM_A16 RAM_A15  |
 * ------------------------------------------------------------------------------------------------
 *      x    |   x    x     |        1           |     0       1     | Phy bank 1 (common fixed)
 *      -    |   0    0     |        0           |     0       1     | Phy bank 1 (common fixed)
 *      0    |   0    1     |        0           |     0       0     | Phy bank 0 (Logical bank 1)
 *      2    |   1    0     |        0           |     1       1     | Phy bank 3 (Logical bank 2)
 *      1    |   1    1     |        0           |     1       0     | Phy bank 2 (Logical bank 3)
 * 
 *       Physical Bank      |    Logical Bank    |   Physical Bank   |   Physical RAM Addresses
 *           number         |       number       |  RAM_A16 RAM_A15  |
 * -------------------------------------------------------------------------------------------------
 *             0            |         1          |    0       0      | From 0x00000 to 0x07FFF
 *             1            |         0          |    0       1      | From 0x08000 to 0x0FFFF
 *             2            |         3          |    1       0      | From 0x01000 to 0x17FFF
 *             3            |         2          |    1       1      | From 0x18000 to 0x1FFFF
 * 
 * NOTE: The Logical Bank 0 can't be used as a switchable OS bank because it is
 * the common fixed bank mapped in the upper half of the Z80 address space (from 0x8000 to 0xFFFF)
 * NOTE: If the OS bank number is greater than 2, no selection is done.
 */
#define OP_IO_WR_SETBNK 0x0D        // Set bank

/**
 * @brief Enable/disable IRQ generation
 * D7 D6 D5 D4 D3 D2 D1 D0
 * ----------------------------------------------------------
 * x  x  x  x  x  x  x  0   Serial RX IRQ not enabled
 * x  x  x  x  x  x  x  1   Serial RX IRQ enabled
 * x  x  x  x  x  x  0  x   SYSTICK IRQ not enabled
 * x  x  x  x  x  x  1  x   SYSTICK IRQ enabled
 * 
 * NOTE: See OP_IO_RD_SYSIRQ for more detail.
 */
#define OP_IO_WR_SETIRQ 0x0E

/**
 * @brief Set the Systick timer time (milliseconds).
 * Set/change the time (milliseconds) used for the Systick timer. At reset
 * time, the default value is 100ms. See OP_IO_RD_SYSIRQ and
 * OP_IO_WR_SETIRQ for more detail.
 * 
 * NOTE: If the time is 0 milliseconds, the set operation is ignored.
 */
#define OP_IO_WR_SETTICK 0x0F

/**
 * @brief Start playing a sound from the PC speaker.
 * 
 * NOTE: Currently only supports a single byte value for frequency which limits
 * max frequency to 255.
 * NOTE: Sound plays until stopped by calling OP_IO_WR_BEEPSTOP.
 */
#define OP_IO_WR_BEEPSTART 0x20

/**
 * @brief Stop playing sound from the PC speaker.
 */
#define OP_IO_WR_BEEPSTOP 0x21

/**
 * I/O Read OpCodes. Follows the same semantics as I/O Write OpCodes.
 * All OpCodes except OP_IO_RD_RDSECT only exchange a single byte. RDSECT can
 * exchange 512 bytes. When it comes I/O Read operations, if PIN_A0 is LOW,
 * then the previously stored OpCode will be executed; Otherwise, a Serial Read
 * operation is executed:
 * NOTE: If there is no input char, a value of 0xFF is forced as input char.
 * NOTE: The PIN_INT signal is always reset (set to HIGH) after this I/O operation.
 * NOTE: This is the only I/O operation that does not require any previous
 * STORE OPCODE operation (for fast polling).
 * NOTE: A "RX buffer empty" flag and a "Last RX char was empty" flag are
 * available in the SYSFLG OpCode to allow 8bit I/O.
 */

/**
 * @brief Reads the USER button. If Bit 7 (PIN_D0) is HIGH,
 * then the button is PRESSED.
 */
#define OP_IO_RD_USRKEY 0x80

/**
 * @brief Read GPIOA on the MCP23017.
 * NOTE: A value of 0x00 is forced if the MCP23017 is not detected.
 */
#define OP_IO_RD_GPIOA 0x81

/**
 * @brief Read GPIOB on the MCP23017.
 * NOTE: A value of 0x00 is forced if the MCP23017 is not detected.
 */
#define OP_IO_RD_GPIOB 0x82

/**
 * @brief Read the SYSFLGs (various system flags for the OS):
 * D7 D6 D5 D4 D3 D2 D1 D0
 * ----------------------------------------------------------
 * x  x  x  x  x  x  x  0   AUTOEXEC disabled
 * x  x  x  x  x  x  x  1   AUTOEXEC enabled
 * x  x  x  x  x  x  0  x   DS1307 RTC not found
 * x  x  x  x  x  x  1  x   DS1307 RTC found
 * x  x  x  x  x  0  x  x   Serial RX buffer empty
 * x  x  x  x  x  1  x  x   Serial RX char available
 * x  x  x  x  0  x  x  x   Previous RX char valid
 * x  x  x  x  1  x  x  x   Previous RX char was a "buffer empty" flag
 * 
 * NOTE: Currently only D0 - D3 are used.
 */
#define OP_IO_RD_SYSFLG 0x83

/**
 * @brief Read the date/time and temperature from the RTC (binary). The data
 * is read sequentially in 7 bytes:
 * Byte 0 = seconds [0..59]
 * Byte 1 = minutes [0..59]
 * Byte 2 = hours [0..23]
 * Byte 3 = day [0..31]
 * Byte 4 = month [1..12]
 * Byte 5 = year [0..99]
 * Byte 6 = tempC [-128..127]
 * 
 * NOTE: If RTC is not found, all read values will be 0.
 * NOTE: Overread data (more than 7 bytes) will be 0.
 * NOTE: The temperature (Celcius) is a byte with two's complement binary
 * format [-128..127].
 */
#define OP_IO_RD_DATTME 0x84

/**
 * @brief DISK EMULATION. Read the error code after a SELDSK, SELSCT, SELTRK,
 * WRTSCT, RDSECT, or SDMNT operation.
 * 
 * Error codes table:
 *    error code   | description
 * ----------------------------------------------------------------------------
 *        0        | No error
 *        1        | DISK_ERR: The function failed due to a hard error in the
 *                 | disk function, a wrong FAT structure or an internal error.
 *        2        | NOT_READY: The storage device could not be initialized due
 *                 | to a hard error or no medium.
 *        3        | NO_FILE: could not find the file.
 *        4        | NOT_OPENED: the file has not been opened.
 *        5        | NOT_ENABLED: the volumen has not been mounted.
 *        6        | NO_FILESYSTEM: there is no valid FAT partition on the drive.
 *       16        | Illegal disk number.
 *       17        | Illegal track number.
 *       18        | Illegal sector number.
 *       19        | Reached an unexpected EOF.
 * 
 * NOTE: ERRDSK code is referred to the previous SELDSK, SELSCT, SELTRK,
 * WRTSCT, or RDSECT operation.
 * NOTE: Error codes from 0 to 6 come from the PetiteFS library implementation.
 * NOTE: ERRDSK must not be used to read the resulting error code after a SDMNT
 * operation (see the OP_IO_RD_SDMNT OpCode).
 */
#define OP_IO_RD_ERRDSK 0x85

/**
 * @brief DISK EMULATION. Read 512 data bytes sequentially from the current
 * emulated disk/track/sector. Reads the current 512 bytes of the current
 * track/sector, one data byte per call. All the 512 calls must be always
 * performed sequentially to have a RDSECT operation correctly done. If an
 * error occurs during the RDSECT operation, all subsequent read data will be 0.
 * If an error occurs calling any DISK EMULATION OpCode (SDMNT excluded)
 * immediately before the RDSECT OpCode call, all the read data will be 0 and 
 * the RDSECT operation will not be performed. Errors are stored into diskErr
 * (see OP_IO_RD_ERRDSK OpCode).
 * 
 * NOTE: Before a RDSECT operation at least SELTRK or a SELSCT must always be
 * performed *first*.
 * NOTE: Remember to open the right "disk file" at first using the SELDSK OpCode.
 */
#define OP_IO_RD_RDSECT 0x86

/**
 * @brief Mount a volume on SD, returning an error code (binary).
 * NOTE: This OpCode is "normally" not used. Only needed if using a virtual
 * disk from a custom program loaded with iLoad or with the Autoboot mode
 * (e.g. ViDiT). Can be used to handle SD hot-swapping.
 * NOTE: For error codes explanation see OP_IO_RD_ERRDSK OpCode.
 * NOTE: Only for this disk OpCode, the resulting error is read as a data
 * byte without using the OP_IO_RD_ERRDSK OpCode.
 */
#define OP_IO_RD_SDMNT 0x87

/**
 * @brief Get the current available free space (in bytes) in the TX buffer. 
 * NOTE: This OpCode is intended to help avoid delays in Serial TX operations,
 * as IOS holds the Z80 in a wait status if the TX buffer is full. This is no
 * good in multitasking environments. Using this OpCode, we can poll the buffer
 * before transmit.
 */
#define OP_IO_RD_ATXBUFF 0x88

/**
 * @brief Get the Interrupt Status Byte (ISB).
 * D7 D6 D5 D4 D3 D2 D1 D0
 * ----------------------------------------------------------
 * x  x  x  x  x  x  x  0   Serial RX IRQ not set
 * x  x  x  x  x  x  x  1   Serial RX IRQ set
 * x  x  x  x  x  x  0  x   SYSTICK IRQ not set
 * x  x  x  x  x  x  1  x   SYSTICK IRQ set
 *
 * The /INT signal is shared among various interrupt requests. This allows the
 * use of the simplified "Mode 1" scheme of the Z80 CPU (fixed jump to 0x0038 on
 * /INT signal active) with multiple interrupt causes. The SYSIRQ purpose is to
 * allow the Z80 CPU to know the exact causes of the interrupt reading the
 * "Interrupt Status Byte" that contains up to eight "Interrupt Status Bits".
 * So the ISR (Interrupt Service Routine) should be structured to first read
 * the "Interrupt Status Byte" using the SYSIRQ OpCode, then execute the needed
 * actions before returning to normal execution. Note multiple causes/bits
 * could be active.
 * 
 * NOTE: Only D0 and D1 "Interrupt Status Bits" are currently used.
 * NOTE: After the SYSIRQ call, all the "Interrupt Status Bits" are cleared.
 * NOTE: The /INT signal is always reset (set HIGH) after this I/O operation,
 * so you always have to call it from inside the ISR (on the Z80 side) before,
 * in order to re-enable the Z80 IRQ again.
 */
#define OP_IO_RD_SYSIRQ 0x89

/**
 * @brief Initializes the CyBorg SPP card. This OpCode is ignored if SPP card is not present.
 * This OpCode peforms the following procedures:
 * - Configure onboard MCP23017 to operate as SPP.
 * - The STROBE (active low) Control Line of the SPP port is set to High;
 * - D0 is used to set the status of AUTOFD (active Low) Control Line of the SPP port (AUTOFD = !D0);
 * - The printer is initialized with a pulse on the INIT (active Low) Control line of the SPP port.
 */
#define OP_SPP_WR_INIT 0x11

/**
 * @brief Sends a byte to the printer attached to the SPP port. This OpCode is ignored if SPP card
 * is not present. No check is done here to know if the printer is ready or not, so you have to use the
 * OP_SPP_RD_READ OpCode before for that.
 * 
 * NOTE: to use OP_SPP_WR_WRITE the OP_SPP_WR_INIT OpCode should be called first to init the SPP card.
 */
#define OP_SPP_WR_WRITE 0x12

/**
 * @brief Read the Status Lines of the SPP Port and the SPP emulation status. This OpCode is
 * ignored if the SPP card is not present.
 * 
 * NOTE: The SPP must be initialized first using OP_SPP_WR_INIT.
 */
#define OP_SPP_RD_READ 0x8A

/**
 * @brief Reserved as No-Op.
 */
#define OP_IO_NOP 0xFF

// TODO Eventually introduce OpCodes for interracting with KAMVA functions (specifically A/V stuff)
// TODO Also opcodes for enabling/disabling slots

/**
 * SD operation types 
 */

#define SD_OP_TYPE_MOUNT 0
#define SD_OP_TYPE_OPEN 1
#define SD_OP_TYPE_READ 2
#define SD_OP_TYPE_WRITE 3
#define SD_OP_TYPE_SEEK 4


/**
 * Disk Emulation Error Codes (see OP_IO_RD_ERRDSK)
 */

#define ERR_DSK_EMU_OK 0
#define ERR_DSK_EMU_DISK_ERR 1
#define ERR_DSK_EMU_NOT_READY 2
#define ERR_DSK_EMU_NO_FILE 3
#define ERR_DSK_EMU_NOT_OPENED 4
#define ERR_DSK_EMU_NOT_ENABLED 5
#define ERR_DSK_EMU_NO_FILESYSTEM 6
#define ERR_DSK_EMU_ILLEGAL_DSK_NUM 16
#define ERR_DSK_EMU_ILLEGAL_TRK_NUM 17
#define ERR_DSK_EMU_ILLEGAL_SCT_NUM 18
#define ERR_DSK_EMU_UNEXPECTED_EOF 19

#endif