/**
 * @brief Ring buffer for u8 data values.
 */
#ifndef EMC_RINGBUF_H
#define EMC_RINGBUF_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum {
    RINGBUF_OK = 0,              
    RINGBUF_ERROR = 1,        
    RINGBUF_ERROR_INIT = 2,
    RINGBUF_ERROR_INVALID_PARAM = 3,
    RINGBUF_ERROR_INVALID_SIZE = 4,
    RINGBUF_ERROR_FULL = 6,         
    RINGBUF_ERROR_EMPTY = 7          
} emc_ringbuf_status_t;

struct emc_ringbuf {
    uint8_t *buf;         /*!< pointer to the buffer memory */
    uint32_t write_idx;   /*!< head - written ONLY by producer */
    uint32_t read_idx;    /*!< tail - written ONLY by consumer */
    uint32_t buf_size;    /*!< size of the buffer, must be a power of two */
    uint32_t mask;        /*!< mask for index wrapping, buf_size -1 */
};


/**
 * Initializes ring buffer object
 * @param rb ring buffer to initialize
 * @param buf memory buffer to store data
 * @param size size of the buffer, must be a power of two
 * @return RINGBUF_OK on success, error code otherwise
 */
emc_ringbuf_status_t emc_ringbuf_init(struct emc_ringbuf *rb, uint8_t *buf, uint32_t size);
void emc_ringbuf_clear(struct emc_ringbuf *rb);

emc_ringbuf_status_t emc_ringbuf_write(struct emc_ringbuf *rb, uint8_t byte);
emc_ringbuf_status_t emc_ringbuf_write_bulk(struct emc_ringbuf *rb, const uint8_t *buf, uint32_t length);  
emc_ringbuf_status_t emc_ringbuf_read(struct emc_ringbuf *rb, uint8_t *byte);
emc_ringbuf_status_t emc_ringbuf_read_bulk(struct emc_ringbuf *rb, uint8_t *buf, uint32_t length);
emc_ringbuf_status_t emc_ringbuf_peek(struct emc_ringbuf *rb, uint8_t *byte);
emc_ringbuf_status_t emc_ringbuf_peek_bulk(struct emc_ringbuf *rb, uint8_t *buf, uint32_t length);

uint32_t emc_ringbuf_available(struct emc_ringbuf *rb);
uint32_t emc_ringbuf_free(struct emc_ringbuf *rb);
bool     emc_ringbuf_is_empty(struct emc_ringbuf *rb);
bool     emc_ringbuf_is_full(struct emc_ringbuf *rb);

#endif // EMC_RINGBUF_H