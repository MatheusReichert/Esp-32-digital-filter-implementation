#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "signal-acquirer.h"

static QueueHandle_t queue;


void readToQueue(){
    int aux = analogRead();
    if(xQueueSend(queue, &aux, pdMS_TO_TICKS(0)) == false){
        printf("Error");
    }
}

void dequeueAndPrint(){
    while(1){
    int receivedValue = 0;
    if(xQueueReceive(queue, &receivedValue, pdMS_TO_TICKS(100)) == true){
        printf("%i\n", receivedValue);
    }
    else{
        printf("Syncro error");
    }
    }
}

void app_main() {

    queue = xQueueCreate(100, sizeof(int));
    adc_calibration();

    TimerHandle_t timer = xTimerCreate(
        "Timer",
        pdMS_TO_TICKS(20),
        pdTRUE,
        0,
        readToQueue
    );

    xTimerStart(timer, 0);
    xTaskCreatePinnedToCore(dequeueAndPrint, "dequeueAndPrint", 4096, NULL, 1, NULL, 1);    

}