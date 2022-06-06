#include"driver/adc.h"
#include"esp_adc_cal.h"

esp_adc_cal_characteristics_t *adc_chars;

esp_adc_cal_value_t adc_calibration();
int analogRead();

