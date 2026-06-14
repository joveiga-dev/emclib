#include "emc_ringbuf.h"


static bool emc_is_power_of_two(uint32_t n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

emc_ringbuf_status_t emc_ringbuf_init(struct emc_ringbuf_s *self, uint8_t *buf, uint32_t size)
{
    if (self == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (!emc_is_power_of_two(size)) {
        return RINGBUF_ERROR_INVALID_SIZE;
    }

    self->buf = buf;
    self->write_idx = 0;
    self->read_idx = 0;
    self->buf_size = size;
    self->mask = size - 1;

    return RINGBUF_OK;

}

void emc_ringbuf_clear(struct emc_ringbuf_s *self)
{
    if (self == NULL) {
        return;
    }

    self->buf = NULL;
    self->write_idx = 0;
    self->read_idx = 0;
    self->buf_size = 0;
    self->mask = 0;
}


uint32_t emc_ringbuf_available(struct emc_ringbuf_s *self)
{
    return (self->write_idx - self->read_idx) & self->mask;
}

uint32_t emc_ringbuf_free(struct emc_ringbuf_s *self)
{
    return self->buf_size - emc_ringbuf_available(self);
    // return (self->write_idx - self->read_idx - 1) & self->mask;
}

bool emc_ringbuf_is_empty(struct emc_ringbuf_s *self)
{
    return (self->write_idx == self->read_idx);
}

bool emc_ringbuf_is_full(struct emc_ringbuf_s *self)
{
    uint32_t next_write_idx = (self->write_idx + 1) & (self->mask);
    return (next_write_idx == self->read_idx);
}

emc_ringbuf_status_t emc_ringbuf_write(struct emc_ringbuf_s *self, uint8_t byte)
{
    if (self == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (emc_ringbuf_is_full(self)) {
        return RINGBUF_ERROR_FULL;
    }

    uint32_t next_write_idx = (self->write_idx + 1) & self->mask;
    self->buf[self->write_idx] = byte;
    self->write_idx = next_write_idx;

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_write_bulk(struct emc_ringbuf_s *self, const uint8_t *buf, uint32_t length)
{
    if (self == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (length > emc_ringbuf_free(self)) {
        return RINGBUF_ERROR_FULL;
    }
    
    // for performance consider writting directly to the buffer
    for (uint32_t i = 0; i < length; i++) {
        uint32_t next_write_idx = (self->write_idx + 1) & self->mask;
        self->buf[self->write_idx] = buf[i];
        self->write_idx = next_write_idx;
    }

    return RINGBUF_OK;

}

emc_ringbuf_status_t emc_ringbuf_read(struct emc_ringbuf_s *self, uint8_t *byte)
{
    if (self == NULL || byte == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }
    if (emc_ringbuf_is_empty(self)) {
        return RINGBUF_ERROR_EMPTY;
    }

    uint32_t next_read_idx = (self->read_idx + 1) & self->mask;
    *byte = self->buf[self->read_idx];
    self->read_idx = next_read_idx;

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_read_bulk(struct emc_ringbuf_s *self, uint8_t *buf, uint32_t length)
{
    if (self == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (length > emc_ringbuf_available(self)) {
        return RINGBUF_ERROR_EMPTY;
    }
    
    for (uint32_t i = 0; i < length; i++) {
        uint32_t next_read_idx = (self->read_idx + 1) & self->mask;
        buf[i] = self->buf[self->read_idx];
        self->read_idx = next_read_idx;
    }

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_peek(struct emc_ringbuf_s *self, uint8_t *byte)
{
    if (self == NULL || byte == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }
    if (emc_ringbuf_is_empty(self)) {
        return RINGBUF_ERROR_EMPTY;
    }

    *byte = self->buf[self->read_idx];

    return RINGBUF_OK;
}

emc_ringbuf_status_t emc_ringbuf_peek_bulk(struct emc_ringbuf_s *self, uint8_t *buf, uint32_t length)
{
    if (self == NULL || buf == NULL) {
        return RINGBUF_ERROR_INVALID_PARAM;
    }

    if (length > emc_ringbuf_available(self)) {
        return RINGBUF_ERROR_EMPTY;
    }
    
    for (uint32_t i = 0; i < length; i++) {
        buf[i] = self->buf[(self->read_idx + i) & self->mask];
    }

    return RINGBUF_OK;
}
