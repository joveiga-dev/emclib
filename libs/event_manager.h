/**
 * @file event_manager.h
 * @brief Time-based event manager for processing events
 * @author JC
 */

 #ifndef EVENT_MANAGER_H
 #define EVENT_MANAGER_H

 #include <stdint.h>
 #include <stddef.h>

 // Forward declaration
 struct emc_event_manager;

 typedef void (*emc_event_fn)(struct emc_event_manager *manager, void *user_data, int32_t event_id);

 // 
 int32_t emc_event_manager_schedule(struct emc_event_manager *manager, int32_t timestamp,
                                      emc_event_fn event_fn, void *user_data);
 int32_t emc_event_manager_stop(struct emc_event_manager *manager, int32_t event_id);
 int32_t emc_event_manager_next_event(struct emc_event_manager *manager);
 void emc_event_manager_process(struct emc_event_manager *manager, int32_t current_time);




 #endif // EVENT_MANAGER_H