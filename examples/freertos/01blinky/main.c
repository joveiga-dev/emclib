#include "board_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define BLINK_PERIOD_MS    500U


static void system_init(void)
{

    emc_time_init(1000U);
    board_led_init(BOARD_LED_GREEN);

}   


void vBlinkTask(void *pvParameters)
{
    (void) pvParameters;
    while (1) {
        board_led_toggle(BOARD_LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(BLINK_PERIOD_MS));
    }
}

int main(void)
{
    system_init();

    xTaskCreate(
        vBlinkTask,                     // Function to run
        "BlinkTask",                    // Task name 
        configMINIMAL_STACK_SIZE,       // Stack size in words
        NULL,                           // Parameters (none in this case)
        tskIDLE_PRIORITY + 1,           // Priority (1 = lowest)
        NULL                            // Task handle
    );


    /* Start the scheduler */
    vTaskStartScheduler();

    while (1) {
        // Should never reach here
    }


}

