/* main.cpp - FreeRTOS Windows Simulator Demo with Timestamps (no file logging)
   Demonstrates communication, sensor, and error-handling tasks
*/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Handles */
QueueHandle_t xSensorQueue;         // Queue for sensor values
SemaphoreHandle_t xUartSemaphore;   // Semaphore for shared UART

/* Task prototypes */
void vTaskA(void* pvParameters); // Communication task
void vTaskB(void* pvParameters); // Sensor task
void vTaskC(void* pvParameters); // Error handling task

/* Utility function for logging with timestamp */
void logMessage(const char* taskName, const char* msg, int value, int useValue) {
    TickType_t tick = xTaskGetTickCount();
    float seconds = tick / 1000.0f; // 1 tick = 1 ms (configTICK_RATE_HZ=1000)

    if (useValue) {
        printf("[%lu ticks | %.2f s][%s] %s %d\n",
            (unsigned long)tick, seconds, taskName, msg, value);
    }
    else {
        printf("[%lu ticks | %.2f s][%s] %s\n",
            (unsigned long)tick, seconds, taskName, msg);
    }
}

int main(void) {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    printf("Starting FreeRTOS demo...\n");

    // Create queue for 5 integers
    xSensorQueue = xQueueCreate(5, sizeof(int));

    // Create binary semaphore for UART
    xUartSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xUartSemaphore); // Start as available

    if (xSensorQueue != NULL && xUartSemaphore != NULL) {
        // Create the tasks (stack size = 200)
        xTaskCreate(vTaskA, "CommTask", 200, NULL, 1, NULL);
        xTaskCreate(vTaskB, "SensorTask", 200, NULL, 1, NULL);
        xTaskCreate(vTaskC, "ErrorTask", 200, NULL, 1, NULL);

        // Start scheduler
        vTaskStartScheduler();
    }
    else {
        printf("Queue or Semaphore creation failed!\n");
    }

    for (;;); // Should never reach here
}

/* TASK IMPLEMENTATIONS */

void vTaskA(void* pvParameters) {
    (void)pvParameters;
    for (;;) {
        if (xSemaphoreTake(xUartSemaphore, portMAX_DELAY) == pdTRUE) {
            logMessage("Task A", "Sending heartbeat...", 0, 0);
            vTaskDelay(pdMS_TO_TICKS(200)); // simulate UART send delay
            xSemaphoreGive(xUartSemaphore);
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // run every 1s
    }
}

void vTaskB(void* pvParameters) {
    (void)pvParameters;
    for (;;) {
        int sensorValue = rand() % 120; // Random 0–119
        logMessage("Task B", "Sensor value =", sensorValue, 1);
        xQueueSend(xSensorQueue, &sensorValue, 0);
        vTaskDelay(pdMS_TO_TICKS(500)); // run every 0.5s
    }
}

void vTaskC(void* pvParameters) {
    (void)pvParameters;
    int receivedValue;
    for (;;) {
        if (xQueueReceive(xSensorQueue, &receivedValue, portMAX_DELAY) == pdPASS) {
            if (receivedValue > 90) {
                logMessage("Task C", "Sensor value out of range! Error flagged:", receivedValue, 1);
            }
            else {
                logMessage("Task C", "Sensor value OK:", receivedValue, 1);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(2000)); // run every 2s
    }
}
