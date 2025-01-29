#ifndef _DISKIO_H
#define _DISKIO_H

#include <stdint.h>

#define MAX_TRACKS 512
#define MAX_SECTORS 32

enum disk_error_t {
    disk_error_ok = 0,
    disk_error_disk_err = 1,
    disk_error_not_ready = 2,
    disk_error_no_files = 3,
    disk_error_not_opened = 4,
    disk_error_not_enabled = 5,
    disk_error_no_filesys = 6,
    disk_error_illegal_dsk_num = 16,
    disk_error_illegal_trk_num = 17,
    disk_error_illegal_sect_num = 18,
    disk_error_unexpected_eof = 19
};

enum disk_error_t diskio_get_last_error(void);
enum disk_error_t diskio_select_disk(uint8_t disk_num);
enum disk_error_t diskio_select_track(uint16_t track_num);
enum disk_error_t diskio_select_sector(uint8_t sector_num);
enum disk_error_t diskio_write_sector(uint16_t data);
enum disk_error_t diskio_read_sector(uint16_t *sect_buf);
enum disk_error_t diskio_mount(void);

#endif