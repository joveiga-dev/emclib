#include "emc_ringbuf_manager.h"


// Notify event callback
static void emc_ringbuf_manager_notify_evt(emc_ringbuf_manager_t *manager, emc_ringbuf_evt_t evt, uint32_t length) 
{
    if (manager->evt_fn == 0) {
        return;
    }

    emc_ringbuf_evt_data_t data = {
        .length = length
    };

    manager->evt_fn(manager, evt, &data, manager->user_data);

}

int emc_ringbuf_manager_init(emc_ringbuf_manager_t *manager, void* buff, uint32_t size, emc_ringbuf_evt_fn_t evt_fn, void *user_data)
{
    if (manager == NULL || buff == NULL || size == 0) {
        return -1;
    }

    int ret = emc_ringbuf_init(&manager->ringbuf, (uint8_t *)buff, size);
    if (ret != RINGBUF_OK) {
        return ret;
    }

    manager->evt_fn = evt_fn;
    manager->user_data = user_data;

    return RINGBUF_OK;
}

void emc_ringbuf_manager_deinit(emc_ringbuf_manager_t *manager)
{
    if (manager == 0) {
        return;
    }

    emc_ringbuf_clear(&manager->ringbuf);
    emc_ringbuf_manager_notify_evt(manager, RINGBUF_EVT_RESET, 0);
}

void emc_ringbuf_manager_set_evt_fn(emc_ringbuf_manager_t *manager, emc_ringbuf_evt_fn_t evt_fn)
{
    if (manager == NULL) {
        return;
    }

    manager->evt_fn = evt_fn;
}

void emc_ringbuf_manager_set_user_data(emc_ringbuf_manager_t *manager, void *user_data)
{
    if (manager == NULL) {
        return;
    }

    manager->user_data = user_data;
}

void *emc_ringbuf_manager_get_user_data(emc_ringbuf_manager_t *manager)
{
    if (manager == NULL) {
        return NULL;
    }

    return manager->user_data;
}

// Read and Write
int emc_ringbuf_manager_write(emc_ringbuf_manager_t *manager, const void *data, uint32_t length)
{
    if (manager == 0 || data == 0 || length == 0) {
        return -1;
    }

    int ret = emc_ringbuf_write_bulk(&manager->ringbuf, (const uint8_t *)data, length);
    if (ret == RINGBUF_OK) {
        emc_ringbuf_manager_notify_evt(manager, RINGBUF_EVT_WRITE, length);
    }

    return ret;
}

int emc_ringbuf_manager_read(emc_ringbuf_manager_t *manager, void *data, uint32_t length)
{
    if (manager == 0 || data == 0 || length == 0) {
        return -1;
    }

    int ret = emc_ringbuf_read_bulk(&manager->ringbuf, (uint8_t *)data, length);
    if (ret == RINGBUF_OK) {
        emc_ringbuf_manager_notify_evt(manager, RINGBUF_EVT_READ, length);
    }

    return ret;
}

int emc_ringbuf_manager_peek(emc_ringbuf_manager_t *manager, void *data, uint32_t length)
{
    if (manager == 0 || data == 0 || length == 0) {
        return -1;
    }

    int ret = emc_ringbuf_peek_bulk(&manager->ringbuf, (uint8_t *)data, length);
    if (ret == RINGBUF_OK) {
        emc_ringbuf_manager_notify_evt(manager, RINGBUF_EVT_READ, length);
    }

    return ret;
}