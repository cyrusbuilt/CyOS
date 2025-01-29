/*-----------------------------------------------------------------------*/
/** @file diskio.c Low level disk I/O module glue functions              */
/*  (C)ChaN, 2016                                                        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h" /* FatFs lower layer API */
#ifdef DRV_MMC
#include <Kernel/Devices/diskio.h>
#endif

static volatile DSTATUS Stat = STA_NOINIT; /* Disk status */

/**
 * Get Drive Status
 */
DSTATUS disk_status(
    BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
    switch (pdrv) {
#ifdef DRV_CFC
        case DRV_CFC:
            return cf_disk_status();
#endif
#ifdef DRV_MMC
        case DRV_MMC:
            return Stat;
#endif
    }
    return STA_NOINIT;
}

/**
 * Initialize a Drive
 */
DSTATUS disk_initialize(
    BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
    enum disk_error_t result = diskio_select_disk(pdrv);
    if (result == disk_error_ok) {
        Stat &= ~STA_NOINIT;
        return Stat;
    }
    return STA_NOINIT;
}

/**
 * Read Sector(s)
 */
DRESULT disk_read(
    BYTE pdrv, /* Physical drive nmuber to identify the drive */
    BYTE* buff, /* Data buffer to store read data */
    DWORD sector, /* Sector address in LBA */
    UINT count /* Number of sectors to read */
)
{
    if (!count) {
        return RES_PARERR;
    }

    if (Stat & STA_NOINIT) {
        return RES_NOTRDY;
    }

    if (sector < MAX_SECTORS) {
        sector *= MAX_TRACKS;
        do {
            enum disk_error_t result = diskio_select_track(sector);

        } while (--count);

        return count ? RES_ERROR : RES_OK;
    }
    return RES_PARERR;
}
