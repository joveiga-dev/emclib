#ifndef EMC_RINGBUF_MANAGER_H
#define EMC_RINGBUF_MANAGER_H

#include "emc_ringbuf.h"

typedef enum {
    RINGBUF_EVT_READ,
    RINGBUF_EVT_WRITE,
    RINGBUF_EVT_RESET
} emc_ringbuf_evt_t;

typedef struct {
    uint32_t length;
} emc_ringbuf_evt_data_t;

struct emc_ringbuf_manager;

/**
 * \brief       Event callback function type
 * \param[in]   manager: Buffer handle for event callback
 * \param[in]   evt: Event type
 */
typedef void (*emc_ringbuf_evt_fn_t)(struct emc_ringbuf_manager *manager, emc_ringbuf_evt_t evt,
     emc_ringbuf_evt_data_t *evt_data, void *user_data);

typedef struct emc_ringbuf_manager {
    struct emc_ringbuf ringbuf;
    emc_ringbuf_evt_fn_t evt_fn;
    void *user_data;
} emc_ringbuf_manager_t;


int emc_ringbuf_manager_init(emc_ringbuf_manager_t *manager, void* buff, uint32_t size, emc_ringbuf_evt_fn_t evt_fn, void *user_data);
void emc_ringbuf_manager_deinit(emc_ringbuf_manager_t *manager);
void emc_ringbuf_manager_set_evt_fn(emc_ringbuf_manager_t *manager, emc_ringbuf_evt_fn_t evt_fn);
void emc_ringbuf_manager_set_user_data(emc_ringbuf_manager_t *manager, void *user_data);
void *emc_ringbuf_manager_get_user_data(emc_ringbuf_manager_t *manager);

// Read and Write
int emc_ringbuf_manager_write(emc_ringbuf_manager_t *manager, const void *data, uint32_t length);
int emc_ringbuf_manager_read(emc_ringbuf_manager_t *manager, void *data, uint32_t length);
int emc_ringbuf_manager_peek(emc_ringbuf_manager_t *manager, void *data, uint32_t length);


#endif // EMC_RINGBUF_MANAGER_H