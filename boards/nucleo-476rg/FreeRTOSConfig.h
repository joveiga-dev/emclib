#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/*-----------------------------------------------------------
 * Hardware configuration
 *----------------------------------------------------------*/

/*
 * Set this to your actual system clock frequency.
 * Change to 4000000UL if your MCU is really running at 4 MHz.
 */
#define configCPU_CLOCK_HZ                       (4000000UL)

#define configTICK_RATE_HZ                       ((TickType_t)1000)
#define configUSE_16_BIT_TICKS                   0

/* Cortex-M interrupt priority configuration */
#define configPRIO_BITS                          4

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY  15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/*-----------------------------------------------------------
 * Scheduler configuration
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                     1
#define configUSE_TIME_SLICING                   1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  1

#define configMAX_PRIORITIES                     5
#define configMINIMAL_STACK_SIZE                 128
#define configMAX_TASK_NAME_LEN                  16
#define configIDLE_SHOULD_YIELD                  1

/*-----------------------------------------------------------
 * Hook functions
 *----------------------------------------------------------*/

#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      1

/*-----------------------------------------------------------
 * Memory allocation
 *----------------------------------------------------------*/

#define configSUPPORT_STATIC_ALLOCATION          0
#define configSUPPORT_DYNAMIC_ALLOCATION         1

#define configTOTAL_HEAP_SIZE                    ((size_t)(10 * 1024))

/*-----------------------------------------------------------
 * Software timers
 *----------------------------------------------------------*/

#define configUSE_TIMERS                         1
#define configTIMER_TASK_PRIORITY                2
#define configTIMER_QUEUE_LENGTH                 10
#define configTIMER_TASK_STACK_DEPTH             256

/*-----------------------------------------------------------
 * Optional features
 *----------------------------------------------------------*/

#define configMESSAGE_BUFFER_LENGTH_TYPE         size_t

#define configENABLE_FPU                         1
#define configENABLE_MPU                         0

/*-----------------------------------------------------------
 * API inclusion
 *----------------------------------------------------------*/

#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                      1
#define INCLUDE_vTaskSuspend                     1
#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_vTaskDelay                       1

/*-----------------------------------------------------------
 * Assertions
 *----------------------------------------------------------*/

#define configASSERT(x)                          \
    if ((x) == 0)                               \
    {                                           \
        taskDISABLE_INTERRUPTS();               \
        for (;;)                                \
        {                                       \
        }                                       \
    }

/*-----------------------------------------------------------
 * CMSIS / STM32 interrupt handlers
 *----------------------------------------------------------*/

#define vPortSVCHandler                          SVC_Handler
#define xPortPendSVHandler                       PendSV_Handler
#define xPortSysTickHandler                      SysTick_Handler

#endif /* FREERTOS_CONFIG_H */