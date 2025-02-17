#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define GPIO_OUTPUT_IO 4
#define GPIO_OUTPUT_PIN_SEL (1ULL<<GPIO_OUTPUT_IO)
#define GPIO_INPUT_IO 2
#define GPIO_INPUT_PIN_SEL (1ULL<<GPIO_INPUT_IO)

int cnt_btn = 0;
static void esantionare_buton(void* arg)
{
    while(1)
    {
        cnt_btn += gpio_get_level(GPIO_INPUT_IO);
    }
    vTaskDelay(1000);
}

void app_main() {
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //set as output mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //start gpio task
    xTaskCreate(esantionare_buton, "esantionare buton", 2048, NULL, 10, NULL);

    int cnt = 0;
    while(1) {
        printf("cnt: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_OUTPUT_IO, cnt % 2);
        
        printf("cnt: %d\n", cnt++);
        gpio_set_level(GPIO_OUTPUT_IO, cnt % 2);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        
        printf("cnt: %d\n", cnt++);
        gpio_set_level(GPIO_OUTPUT_IO, cnt % 2);
        vTaskDelay(250 / portTICK_PERIOD_MS);
        
        printf("cnt: %d\n", cnt++);
        gpio_set_level(GPIO_OUTPUT_IO, cnt % 2);
        vTaskDelay(750 / portTICK_PERIOD_MS);
    }
}
