/**
 * @file emc_log.h
 * @brief Simple logging library
 */


#ifndef EMC_LOG_H
#define EMC_LOG_H

#include <stddef.h>
#include <stdint.h>

/* UART redirection */
#include "emc_uart.h"

#ifndef EMC_LOG_BUFFER_SIZE
#define EMC_LOG_BUFFER_SIZE  1024
#endif

#define EMC_LOG_COLORED 1

typedef enum {
    EMC_LOG_NONE = 0,    /*< No logging */
    EMC_LOG_ERR,
    EMC_LOG_WARN,
    EMC_LOG_INFO,
    EMC_LOG_DBG
} emc_log_level_t;

/* Initialize the logging*/
void emc_log_init(emc_uart_t *uart);
void emc_log_print(emc_log_level_t level, const char *module, const char *msg, ...);
/* Log in hexadecimal */
void emc_log_buffer_hex(emc_log_level_t level, const char *module, const uint8_t *buf, size_t length);
/* Set log level */
void emc_set_log_level(emc_log_level_t level);
emc_log_level_t emc_get_log_level(void);

#define EMC_LOGE(module, ...) \
    emc_log_print(EMC_LOG_ERR, module, __VA_ARGS__)
#define EMC_LOGW(module, ...) \
    emc_log_print(EMC_LOG_WARN, module, __VA_ARGS__)
#define EMC_LOGI(module, ...) \
    emc_log_print(EMC_LOG_INFO, module, __VA_ARGS__)
#define EMC_LOGD(module, ...) \
    emc_log_print(EMC_LOG_DBG, module, __VA_ARGS__)



#endif // EMC_LOG_H