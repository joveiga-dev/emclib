#ifndef EMC_COMMON_H
#define EMC_COMMON_H

// Define some common header files
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define BIT(pos) ((0x1UL) << pos)
#define SET_BIT(REG, BIT)        ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)      ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)       ((REG) & (BIT))
#define WRITE_REG(REG, VAL)       ((REG) = (VAL))
#define CLEAR_REG(REG)            ((REG) = (0x0))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  ((REG) = (((REG) & (~(CLEARMASK))) | (SETMASK)))

typedef enum {
    EMC_STATUS_OK = 0, /*< Operation successful */
    EMC_STATUS_ERR,    /*< Operation failed generic error */
    EMC_STATUS_BUSY,   /*< Peripheral is busy */
    EMC_STATUS_TIMEOUT, /*< Operation timed out */
    EMC_STATUS_NOT_SUPPORTED, /*< Operation not supported */
    EMC_STATUS_ALREADY_INITIALIZED, /*< Peripheral already initialized */
    EMC_STATUS_NOT_INITIALIZED, /*< Peripheral not initialized */
} emc_result_t;


#endif // EMC_COMMON_H