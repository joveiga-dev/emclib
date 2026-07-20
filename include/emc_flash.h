/**
 * @file emc_flash.h
 *  Flash memory module
 * @author JC
 */

#ifndef EMC_FLASH_H
#define EMC_FLASH_H

#include "emc_common.h"

typedef enum {
    EMC_FLASH_COMPLETE = 0,
    EMC_FLASH_BUSY,
    EMC_FLASH_ERROR
} emc_flash_status_t;

typedef struct {
    uint32_t start_address;
    uint32_t size;
    uint32_t page_size;
} emc_flash_info_t;

emc_result_t emc_flash_init(void);
emc_result_t emc_flash_deinit(void);

emc_result_t emc_flash_read(uint32_t addr, void *data, uint32_t len);
emc_result_t emc_flash_write(uint32_t addr, const void *data, uint32_t len);

emc_result_t emc_flash_erase_page(uint32_t addr);
emc_result_t emc_flash_erase_chip(void);

emc_result_t emc_flash_get_info(emc_flash_info_t *info);
bool emc_flash_is_busy(void);


#endif // EMC_FLASH_H