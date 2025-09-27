#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Minimal FreeRTOSConfig for Windows simulator demo
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION            1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configTICK_RATE_HZ              (1000)   // 1 ms tick
#define configMINIMAL_STACK_SIZE        ((unsigned short)70)
#define configTOTAL_HEAP_SIZE           ((size_t)(75 * 1024)) // 75 KB
#define configMAX_TASK_NAME_LEN         12
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configMAX_PRIORITIES            5

/* Mutexes, semaphores, queues */
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1
#define configUSE_QUEUE_SETS            1

/* API function inclusion */
#define INCLUDE_vTaskDelay              1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_uxTaskPriorityGet       1
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#define INCLUDE_xTaskGetSchedulerState  1

#endif /* FREERTOS_CONFIG_H */
