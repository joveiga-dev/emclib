/**
 * @file test_ringbuf.c
 * 
 * Unit tests for emc_ringbuf
 * 
 * @author JC
 * 
 */


#include <stdio.h>
#include <assert.h>
#include "emc_ringbuf.h"

static uint8_t BUFFER[8];
static struct emc_ringbuf rb;

void setup(void) {}
void teardown(void) {}

void _test_write_read(struct emc_ringbuf *rb, uint8_t *buf, uint32_t size);





void test_write_read(void) {
    emc_ringbuf_init(&rb, BUFFER, sizeof(BUFFER));
    uint8_t data[] = {1, 2, 3, 4, 5};
    for (uint8_t i = 0; i < sizeof(data); i++) {
        emc_ringbuf_write(&rb, data[i]);

        uint8_t byte;
        emc_ringbuf_read(&rb, &byte);
        assert(byte == data[i]);

        printf("Written: %d, Read: %d\n", data[i], byte);
    }
}

void test_fifo()
{
    emc_ringbuf_init(&rb, BUFFER, sizeof(BUFFER));

    uint8_t i;

    for (i = 1; i <= 4; i++)
        emc_ringbuf_write(&rb, i);

    uint8_t out;

    for (i = 1; i <= 4; i++)
    {
        emc_ringbuf_read(&rb, &out);
        assert(out == i);
    }

    printf("test_fifo PASSED\n");
}

void test_overflow()
{
    emc_ringbuf_init(&rb, BUFFER, sizeof(BUFFER));

    uint8_t val = 1;

    for (uint8_t i = 0; i < 8; i++)
    {
        emc_ringbuf_status_t st =
            emc_ringbuf_write(&rb, val);

        if (st == RINGBUF_ERROR_FULL)
        {
            printf("Buffer full at i=%d\n", i);
            break;
        }
    }

    printf("test_overflow PASSED\n");
}

void test_wrap()
{
    emc_ringbuf_status_t st;

    st = emc_ringbuf_init(&rb, BUFFER, sizeof(BUFFER));

    assert(st == RINGBUF_OK);

    printf("Capacity: %d\n", emc_ringbuf_free(&rb));

    uint8_t v;
    for (v = 1; v <= 7; v++)
    {
        st = emc_ringbuf_write(&rb, v);
        printf("WRITE value: %d, Status: %d\n", v, st);
        assert(st == RINGBUF_OK);
    }

    uint8_t out;
    for (v = 1; v <= 7; v++)
    {
        st = emc_ringbuf_read(&rb, &out);
        printf("READ value: %d, Status: %d\n", out, st);

        assert(st == RINGBUF_OK);
        assert(out == v);
    }

    assert(emc_ringbuf_is_empty(&rb));

    printf("test_wrap PASSED\n");
}

int main()
{
    test_write_read();
    test_fifo();
    test_overflow();
    test_wrap();

    return 0;
}
