#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

#define SERVO_PIN GPIO_NUM_17
#define SERVO_TIMER LEDC_TIMER_0
#define SERVO_CHANNEL LEDC_CHANNEL_0
#define SERVO_FREQ_HS 261
#define SERVO_SPEED_MOD LEDC_LOW_SPEED_MODE
#define KEY_PIN1 GPIO_NUM_4
#define KEY_PIN2 GPIO_NUM_5
#define KEY_PIN3 GPIO_NUM_6
#define KEY_PIN4 GPIO_NUM_7
#define KEY_PIN5 GPIO_NUM_15
#define KEY_PIN6 GPIO_NUM_16
#define BEEP_DUTY 500
#define BEEP_TIME 200
esp_timer_handle_t xTimer_Key1 = NULL;
esp_timer_handle_t xTimer_Key2 = NULL;
esp_timer_handle_t xTimer_Key3 = NULL;
esp_timer_handle_t xTimer_Key4 = NULL;
esp_timer_handle_t xTimer_Key5 = NULL;
esp_timer_handle_t xTimer_Key6 = NULL;

void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;

    if (gpio_num == KEY_PIN1)
    {
        // 按键1的中断处理逻辑
        esp_timer_start_once(xTimer_Key1, 20000);
    }
    else if (gpio_num == KEY_PIN2)
    {
        // 按键2的中断处理逻辑
        esp_timer_start_once(xTimer_Key2, 20000);
    }
    else if (gpio_num == KEY_PIN3)
    {
        // 按键3的中断处理逻辑
        esp_timer_start_once(xTimer_Key3, 20000);
    }
    if (gpio_num == KEY_PIN4)
    {
        // 按键4的中断处理逻辑
        esp_timer_start_once(xTimer_Key4, 20000);
    }
    else if (gpio_num == KEY_PIN5)
    {
        // 按键5的中断处理逻辑
        esp_timer_start_once(xTimer_Key5, 20000);
    }
    else if (gpio_num == KEY_PIN6)
    {
        // 按键6的中断处理逻辑
        esp_timer_start_once(xTimer_Key6, 20000);
    }
}

void timer_key_cb1(void *args)
{
    if (gpio_get_level(KEY_PIN1) == 1)
    {
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, BEEP_DUTY);
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
        ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, 261);
        vTaskDelay(pdMS_TO_TICKS(BEEP_TIME));
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    }
}
void timer_key_cb2(void *args)
{
    if (gpio_get_level(KEY_PIN2) == 1)
    {
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, BEEP_DUTY);
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
        ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, 293);
        vTaskDelay(pdMS_TO_TICKS(BEEP_TIME));
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    }
}
void timer_key_cb3(void *args)
{
    if (gpio_get_level(KEY_PIN3) == 1)
    {
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, BEEP_DUTY);
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
        ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, 329);
        vTaskDelay(pdMS_TO_TICKS(BEEP_TIME));
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    }
}
void timer_key_cb4(void *args)
{
    if (gpio_get_level(KEY_PIN4) == 1)
    {
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, BEEP_DUTY);
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
        ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, 349);
        vTaskDelay(pdMS_TO_TICKS(BEEP_TIME));
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    }
}
void timer_key_cb5(void *args)
{
    if (gpio_get_level(KEY_PIN5) == 1)
    {
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, BEEP_DUTY);
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
        ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, 392);
        vTaskDelay(pdMS_TO_TICKS(BEEP_TIME));
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    }
}
void timer_key_cb6(void *args)
{
    if (gpio_get_level(KEY_PIN6) == 1)
    {
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, BEEP_DUTY);
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
        ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, 440);
        vTaskDelay(pdMS_TO_TICKS(BEEP_TIME));
        ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
        ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    }
}

void app_main(void)
{
    gpio_pad_select_gpio(SERVO_PIN);
    gpio_set_direction(SERVO_PIN, GPIO_MODE_OUTPUT);

    ledc_timer_config_t timer_cfg = {
        .speed_mode = SERVO_SPEED_MOD,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = SERVO_TIMER,
        .freq_hz = SERVO_FREQ_HS};
    ledc_timer_config(&timer_cfg);

    ledc_channel_config_t pwm_cfg = {
        .speed_mode = SERVO_SPEED_MOD,
        .timer_sel = SERVO_TIMER,
        .channel = SERVO_CHANNEL,
        .gpio_num = SERVO_PIN,
        .duty = 0};
    ledc_channel_config(&pwm_cfg);

    // 配置按键1的gpio_config
    gpio_config_t key_cnf1 = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << KEY_PIN1,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_install_isr_service(0);
    gpio_config(&key_cnf1);
    gpio_isr_handler_add(KEY_PIN1, gpio_isr_handler, (void *)KEY_PIN1);

    // 配置按键2的gpio_config
    gpio_config_t key_cnf2 = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << KEY_PIN2,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&key_cnf2);
    gpio_isr_handler_add(KEY_PIN2, gpio_isr_handler, (void *)KEY_PIN2);

    // 配置按键3的gpio_config
    gpio_config_t key_cnf3 = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << KEY_PIN3,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&key_cnf3);
    gpio_isr_handler_add(KEY_PIN3, gpio_isr_handler, (void *)KEY_PIN3);

    // 配置按键4的gpio_config
    gpio_config_t key_cnf4 = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << KEY_PIN4,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&key_cnf4);
    gpio_isr_handler_add(KEY_PIN4, gpio_isr_handler, (void *)KEY_PIN4);

    // 配置按键5的gpio_config
    gpio_config_t key_cnf5 = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << KEY_PIN5,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&key_cnf5);
    gpio_isr_handler_add(KEY_PIN5, gpio_isr_handler, (void *)KEY_PIN5);

    // 配置按键6的gpio_config
    gpio_config_t key_cnf6 = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << KEY_PIN6,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&key_cnf6);
    gpio_isr_handler_add(KEY_PIN6, gpio_isr_handler, (void *)KEY_PIN6);

    esp_timer_create_args_t timer_args1 = {
        .callback = &timer_key_cb1,
        .name = "Key-Timer"};
    esp_timer_create(&timer_args1, &xTimer_Key1);

    esp_timer_create_args_t timer_args2 = {
        .callback = &timer_key_cb2,
        .name = "Key-Timer2"};
    esp_timer_create(&timer_args2, &xTimer_Key2);

    esp_timer_create_args_t timer_args3 = {
        .callback = &timer_key_cb3,
        .name = "Key-Timer3"};
    esp_timer_create(&timer_args3, &xTimer_Key3);

    esp_timer_create_args_t timer_args4 = {
        .callback = &timer_key_cb4,
        .name = "Key-Timer4"};
    esp_timer_create(&timer_args4, &xTimer_Key4);

    esp_timer_create_args_t timer_args5 = {
        .callback = &timer_key_cb5,
        .name = "Key-Timer5"};
    esp_timer_create(&timer_args5, &xTimer_Key5);

    esp_timer_create_args_t timer_args6 = {
        .callback = &timer_key_cb6,
        .name = "Key-Timer6"};
    esp_timer_create(&timer_args6, &xTimer_Key6);
    // int song[] = {5, 3, 5, 3, 5, 3, 1, 2, 4, 3, 2, 5, 5, 3, 5, 3, 5, 3, 1, 2, 4, 3, 2, 1, 2, 2, 4, 4, 3, 1, 5, 2, 4, 3, 2, 5, 5, 3, 5, 3, 5, 3, 1, 2, 4, 3, 2, 1};
    // int music[] = {262, 294, 330, 349, 392, 440};
    // int length = sizeof(song) / song[0];
    // int i = 0;
    // while (1)
    // {
    //     for (i = 0; i < length; i++)
    //     {
    //         ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 50);
    //         ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    //         ledc_set_freq(SERVO_SPEED_MOD, SERVO_CHANNEL, music[song[i] - 1]);
    //         vTaskDelay(pdMS_TO_TICKS(300));
    //         ledc_set_duty(SERVO_SPEED_MOD, SERVO_CHANNEL, 0); // 将占空比设置为零，停止蜂鸣器的声音
    //         ledc_update_duty(SERVO_SPEED_MOD, SERVO_CHANNEL);
    //         vTaskDelay(pdMS_TO_TICKS(300));
    //     }
    //     if (i == length)
    //         i = 0;
    // }

    vTaskDelete(NULL);
}
