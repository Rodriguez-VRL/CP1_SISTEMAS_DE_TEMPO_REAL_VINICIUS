
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
 
static SemaphoreHandle_t semTask1;
static SemaphoreHandle_t semTask2;
static SemaphoreHandle_t semTask3;
 
void task1(void *pvParameters) {
    while (true) {
        xSemaphoreTake(semTask1, portMAX_DELAY);
        printf("Vinicius Rodrigues - task 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(semTask2);
    }
}

void task2(void *pvParameters) {
    while (true) {
        xSemaphoreTake(semTask2, portMAX_DELAY);
        printf("Vinicius Rodrigues - task 2\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(semTask3);
    }
}
 
void task3(void *pvParameters) {
    while (true) {
        xSemaphoreTake(semTask3, portMAX_DELAY);
        printf("Vinicius Rodrigues - task 3\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(semTask1);
    }
}
 
 
void app_main(void)
{
semTask1 = xSemaphoreCreateBinary();
semTask2 = xSemaphoreCreateBinary();
semTask3 = xSemaphoreCreateBinary();
 
if (!semTask1 || !semTask2 || !semTask3) {
        printf("Erro ao criar semáforos\n");
        return;
}
 
xSemaphoreGive(semTask1);
 
xTaskCreate(task1, "Task1", 2048, NULL, 5, NULL);
xTaskCreate(task2, "Task2", 2048, NULL, 5, NULL);
xTaskCreate(task3, "Task3", 2048, NULL, 5, NULL);
 
}