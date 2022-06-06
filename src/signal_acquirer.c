#include"signal_acquirer.h"

esp_adc_cal_value_t adc_calibration(){
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
esp_adc_cal_value_t val_type = 
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, adc_chars);

    return val_type;
}

int analogRead(){
    return esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC_CHANNEL_7), adc_chars);
}