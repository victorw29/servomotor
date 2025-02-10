//Definição das bibliotecas
#include <pico/stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h" //Configura o hardware para controle do pwm
#include "hardware/clocks.h" //Possui funções para configurar e manipular os clocks da pico w

//Definição dos pinos e funções do código
#define SERVO_PIN 22  //Define o pino do servomotor
#define LED_PIN 12    //Define pino de led para eventuais incrementos
#define PWM_FREQ 50 // 50Hz -> período de 20ms
#define MIN_PULSE 500   // 0° posição (500µs) (0,025%)
#define MID_PULSE 1470  // 90° posição (1470µs) (0,0735%)
#define MAX_PULSE 2400  // 180° posição (2400µs) (0,12%)
#define STEP_PULSE 5    // Incremento suave para movimento
#define STEP_DELAY 10   // Atraso entre movimentos suaves (10ms)

void set_servo_position(uint slice_num, uint channel, uint32_t pulse_width_us) {
    uint32_t clock_freq = 125000000; // Frequência fixa do clock do sistema (125 MHz)
    uint32_t wrap = (clock_freq / PWM_FREQ) - 1; // Ajuste correto do PWM wrap
    uint32_t level = (pulse_width_us * (wrap + 1)) / 20000; // Conversão para duty cycle
    
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, channel, level);
    pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);
    
    pwm_set_clkdiv(slice_num, 125.0f); // Ajuste da divisão de clock para precisão
    pwm_set_enabled(slice_num, true);

    while (1) {
        // Posição 180°
        set_servo_position(slice_num, channel, MAX_PULSE);
        sleep_ms(5000); //Pausa de 5 segundos

        // Posição 90°
        set_servo_position(slice_num, channel, MID_PULSE);
        sleep_ms(5000); //Pausa de 5 segundos

        // Posição 0°
        set_servo_position(slice_num, channel, MIN_PULSE);
        sleep_ms(5000); //Pausa de 5 segundos

        // Movimentação suave entre 0° e 180°
        for (uint32_t pos = MIN_PULSE; pos <= MAX_PULSE; pos += STEP_PULSE) {
            set_servo_position(slice_num, channel, pos);
            sleep_ms(STEP_DELAY);
        }
        for (uint32_t pos = MAX_PULSE; pos >= MIN_PULSE; pos -= STEP_PULSE) {
            set_servo_position(slice_num, channel, pos);
            sleep_ms(STEP_DELAY);
        }
    }
}
