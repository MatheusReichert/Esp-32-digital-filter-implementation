#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "signal_acquirer.h"
#include "filter_moving_average.h"

static QueueHandle_t queue;


void readToQueue(){
    int aux = analogRead();
    if(xQueueSend(queue, &aux, pdMS_TO_TICKS(0)) == false){
        printf("Error, full queue");
    }
}

void dequeueAndPrint(){
    while(1){
    int readValue = 0;
    if(xQueueReceive(queue, &readValue, pdMS_TO_TICKS(100)) == true){
        moving_average(readValue);
        printf("%i %i\n", readValue, mv_filtered );
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