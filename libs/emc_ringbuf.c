#include "emc_ringbuf.h"


static bool is_power_of_two(uint32_t n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

emc_ringbuf_status_t emc_ringbuf_init(struct emc_ringbuf *rb, uint8_t *buf, uint32_t size)
{
    if (rb == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (!is_power_of_two(size)) {
        return RINGBUF_ERROR_INVALID_SIZE;
    }

    rb->buf = buf;
    rb->write_idx = 0;
    rb->read_idx = 0;
    rb->buf_size = size;
    rb->mask = size - 1;

    return RINGBUF_OK;

}

void emc_ringbuf_clear(struct emc_ringbuf *rb)
{
    if (rb == NULL) {
        return;
    }

    rb->buf = NULL;
    rb->write_idx = 0;
    rb->read_idx = 0;
    rb->buf_size = 0;
    rb->mask = 0;
}


uint32_t emc_ringbuf_available(struct emc_ringbuf *rb)
{
    return (rb->write_idx - rb->read_idx) & rb->mask;
}

uint32_t emc_ringbuf_free(struct emc_ringbuf *rb)
{
    return rb->buf_size - emc_ringbuf_available(rb);
    // return (rb->write_idx - rb->read_idx - 1) & rb->mask;
}

bool emc_ringbuf_is_empty(struct emc_ringbuf *rb)
{
    return (rb->write_idx == rb->read_idx);
}

bool emc_ringbuf_is_full(struct emc_ringbuf *rb)
{
    uint32_t next_write_idx = (rb->write_idx + 1) & (rb->mask);
    return (next_write_idx == rb->read_idx);
}

emc_ringbuf_status_t emc_ringbuf_write(struct emc_ringbuf *rb, uint8_t byte)
{
    if (rb == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (emc_ringbuf_is_full(rb)) {
        return RINGBUF_ERROR_FULL;
    }

    uint32_t next_write_idx = (rb->write_idx + 1) & rb->mask;
    rb->buf[rb->write_idx] = byte;
    rb->write_idx = next_write_idx;

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_write_bulk(struct emc_ringbuf *rb, const uint8_t *buf, uint32_t length)
{
    if (rb == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (length > emc_ringbuf_free(rb)) {
        return RINGBUF_ERROR_FULL;
    }
    
    // for performance consider writting directly to the buffer
    for (uint32_t i = 0; i < length; i++) {
        uint32_t next_write_idx = (rb->write_idx + 1) & rb->mask;
        rb->buf[rb->write_idx] = buf[i];
        rb->write_idx = next_write_idx;
    }

    return RINGBUF_OK;

}

emc_ringbuf_status_t emc_ringbuf_read(struct emc_ringbuf *rb, uint8_t *byte)
{
    if (rb == NULL || byte == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }
    if (emc_ringbuf_is_empty(rb)) {
        return RINGBUF_ERROR_EMPTY;
    }

    uint32_t next_read_idx = (rb->read_idx + 1) & rb->mask;
    *byte = rb->buf[rb->read_idx];
    rb->read_idx = next_read_idx;

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_read_bulk(struct emc_ringbuf *rb, uint8_t *buf, uint32_t length)
{
    if (rb == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (length > emc_ringbuf_available(rb)) {
        return RINGBUF_ERROR_EMPTY;
    }
    
    for (uint32_t i = 0; i < length; i++) {
        uint32_t next_read_idx = (rb->read_idx + 1) & rb->mask;
        buf[i] = rb->buf[rb->read_idx];
        rb->read_idx = next_read_idx;
    }

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_peek(struct emc_ringbuf *rb, uint8_t *byte)
{
    if (rb == NULL || byte == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }
    if (emc_ringbuf_is_empty(rb)) {
        return RINGBUF_ERROR_EMPTY;
    }

    *byte = rb->buf[rb->read_idx];

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_peek_bulk(struct emc_ringbuf *rb, uint8_t *buf, uint32_t length)
{
    if (rb == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (length > emc_ringbuf_available(rb)) {
        return RINGBUF_ERROR_EMPTY;
    }
    
    for (uint32_t i = 0; i < length; i++) {
        buf[i] = rb->buf[(rb->read_idx + i) & rb->mask];
    }

    return RINGBUF_OK;
}
