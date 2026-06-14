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

struct emc_ringbuf_s {
    uint8_t *buf;
    uint32_t write_idx;
    uint32_t read_idx;
    uint32_t buf_size;
    uint32_t mask;        // mask for index wrapping, buf_size  must be a power of two
};

// API functions prototypes
emc_ringbuf_status_t emc_ringbuf_init(struct emc_ringbuf_s *self, uint8_t *buf, uint32_t size);
void emc_ringbuf_clear(struct emc_ringbuf_s *self);

emc_ringbuf_status_t emc_ringbuf_write(struct emc_ringbuf_s *self, uint8_t byte);
emc_ringbuf_status_t emc_ringbuf_write_bulk(struct emc_ringbuf_s *self, const uint8_t *buf, uint32_t length);  
emc_ringbuf_status_t emc_ringbuf_read(struct emc_ringbuf_s *self, uint8_t *byte);
emc_ringbuf_status_t emc_ringbuf_read_bulk(struct emc_ringbuf_s *self, uint8_t *buf, uint32_t length);
emc_ringbuf_status_t emc_ringbuf_peek(struct emc_ringbuf_s *self, uint8_t *byte);
emc_ringbuf_status_t emc_ringbuf_peek_bulk(struct emc_ringbuf_s *self, uint8_t *buf, uint32_t length);

uint32_t emc_ringbuf_available(struct emc_ringbuf_s *self);
uint32_t emc_ringbuf_free(struct emc_ringbuf_s *self);
bool     emc_ringbuf_is_empty(struct emc_ringbuf_s *self);
bool     emc_ringbuf_is_full(struct emc_ringbuf_s *self);

#endif // EMC_RINGBUF_H