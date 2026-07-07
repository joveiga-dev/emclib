/**
 * @file emc_clock.h
 * @brief Clock library
 * @note Its provides common apis for clock configuration and management.
 * @author JC
 */

 #ifndef EMC_CLOCK_H
 #define EMC_CLOCK_H

 #include "emc_common.h"


typedef enum {
    EMC_CLOCK_CPU = 0,
    EMC_CLOCK_BUS
} emc_clock_domain_t;

 typedef struct {
    uint32_t cpu_freq;      /**< CPU/System clock (HZ) */
    uint32_t bus_freq;      /**< Bus clock (HZ) */
 } emc_clock_info_t;

 /**
  * @brief Get the clock frequency for a specific domain
  * @param domain: Clock domain to query
  */
 uint32_t emc_clock_get_freq(emc_clock_domain_t domain);
 /**
  * @brief Get the peripheral clock frequency
  * @param periph: Peripheral identifier
  * @return Clock frequency in Hz
  */
 uint32_t emc_clock_get_periph_freq(uint32_t periph);

 /**
  * @brief Get clock information
  * @param info: Pointer to emc_clock_info_t structure to be filled with clock information
  * @return EMC_STATUS_OK on success, error code otherwise
  */
 emc_result_t emc_clock_get_info(emc_clock_info_t *info);

 /**
  * @brief Update the clock system
  * @return EMC_STATUS_OK on success, error code otherwise
  */
 emc_result_t emc_clock_update(void);
 /**
  * @brief Dump the clock information
  */
 void emc_clock_dump(void);



#endif /* EMC_CLOCK_H */