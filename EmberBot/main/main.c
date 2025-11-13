    #include <stdio.h>
    #include "driver/adc.h"
    #include "driver/gpio.h"
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"

    #define FLAME_SENSOR_ANALOG_PIN ADC1_CHANNEL_0  //GPIO36 (ADC1_CH0)
    #define FLAME_SENSOR_DIGITAL_PIN GPIO_NUM_18    //GPIO18


    void Flame_Sensor(int iter) {
        // Configuration for Flame Detection
        // Manual Change in Sensitivity of Detection - Potentiometer 
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(FLAME_SENSOR_ANALOG_PIN, ADC_ATTEN_DB_12);
        gpio_set_direction(FLAME_SENSOR_DIGITAL_PIN, GPIO_MODE_INPUT); // Configure Digital Detection
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(FLAME_SENSOR_ANALOG_PIN, ADC_ATTEN_DB_12); //Configure Analog Detection
        gpio_set_direction(FLAME_SENSOR_DIGITAL_PIN, GPIO_MODE_INPUT); //Configure GPIO
        int analog_value = adc1_get_raw(FLAME_SENSOR_ANALOG_PIN);
        int digital_value = gpio_get_level(FLAME_SENSOR_DIGITAL_PIN);

        printf("Iteration #%d: Analog = %d, Threshold = %s\n", 
            iter, analog_value, digital_value ? "Flame Detected" : "No Flame"); 
    }


    void app_main(void) {
        printf("KY-026 Flame Detection\n");
        int iter = 0;
        while (1) {
            Flame_Sensor(iter++);
            vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 second
        }
    }
