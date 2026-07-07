#include "emc_log.h"
#include <stdio.h>
#include "emc_uart.h"
#include "emc_time.h"


#include <stdarg.h>
#include <stdio.h>

static emc_uart_t *log_uart = NULL;
static emc_log_level_t curr_log_level = EMC_LOG_INFO;

/* Colours ANSI escape codes */
#if EMC_LOG_COLORED
#define LOG_COLOR_ERR_RED         "\033[31m"
#define LOG_COLOR_WARN_YELLOW     "\033[33m"
#define LOG_COLOR_INFO_GREEN      "\033[32m"
#define LOG_COLOR_DBG_CYAN        "\033[36m"
#define LOG_COLOR_RESET           "\033[0m"
#else
#define LOG_COLOR_RESET           ""
#define LOG_COLOR_ERR_RED         ""
#define LOG_COLOR_WARN_YELLOW     ""
#define LOG_COLOR_INFO_GREEN      ""
#define LOG_COLOR_DBG_CYAN        ""
#define LOG_COLOR_RESET           ""
#endif

typedef struct {
    const char *level_str;
    const char *ansi_color;
} emc_log_desc_t;


static const emc_log_desc_t emc_log_get_desc[] = 
{
    [EMC_LOG_ERR] = { "ERROR", LOG_COLOR_ERR_RED },
    [EMC_LOG_WARN] = { "WARN", LOG_COLOR_WARN_YELLOW },
    [EMC_LOG_INFO] = { "INFO", LOG_COLOR_INFO_GREEN },
    [EMC_LOG_DBG] = { "DEBUG", LOG_COLOR_DBG_CYAN }
};

void emc_log_init(emc_uart_t *uart) {
    // Initialize the UART for logging
    log_uart = uart;
}

void emc_set_log_level(emc_log_level_t level) {
    if (level == EMC_LOG_NONE) {
        curr_log_level = level;
    }
}


void emc_log_print(emc_log_level_t level, const char *module, const char *msg, ...) 
{
    
    if(level == EMC_LOG_NONE || level > EMC_LOG_DBG) {
        return; 
    }

    va_list args;
    char buffer[64];
    char message[192];
    va_start(args, msg);
    vsnprintf(buffer, sizeof(buffer), msg, args);
    va_end(args);

    // Get the current timestamp
    emc_time_timestamp_t timestamp;
    emc_time_get_timestamp(&timestamp);

    snprintf(message, sizeof(message), "%s[%02lu:%02lu:%02lu.%03lu][%-5s][%-8s] %s%s\r\n",emc_log_get_desc[level].ansi_color,
            (unsigned long)timestamp.hours, (unsigned long)timestamp.minutes, (unsigned long)timestamp.seconds, 
            (unsigned long)timestamp.milliseconds,emc_log_get_desc[level].level_str,module, buffer,LOG_COLOR_RESET);

    emc_uart_transmit_string(log_uart, message);
}
