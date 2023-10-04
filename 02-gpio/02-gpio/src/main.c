/***********************************************************************
 * 
 * Blink two LEDs in Arduino-, register-, and library-style. Use 
 * function from delay library to slow down blinking.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2019 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED
                        // is connected
#define LED_RED PB0     // Off-board LED
#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
#include <gpio.h>       // GPIO library for AVR-GCC


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
//#include "Arduino.h"
#define PB5 5          // In Arduino world, PB5 is called "13"
#define PB0 0
#define BTN 2
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle LEDs and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    uint8_t led_value = 0;  // Local variable to keep LED status

    // Set pins where LEDs are connected as output
    // Ver 1: Arduino style
    //pinMode(LED_GREEN, OUTPUT);
    //pinMode(LED_RED, OUTPUT);

    // Ver 2: Low-level (register) style
    //DDRB |= (1 << LED_GREEN);
    //DDRB |= (1 << LED_RED);

    // Ver 3: Library function style
    GPIO_mode_output(&DDRB, LED_GREEN);
    GPIO_mode_output(&DDRB, LED_RED);
    GPIO_mode_input_pullup(&DDRD, BTN);


    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        if (GPIO_read(&PIND, BTN) == 0)
        {
            // Change LED value
            if (led_value == 0) {
                led_value = 1;
                // Set pin(s) to HIGH
                //digitalWrite(LED_GREEN, HIGH);
                //digitalWrite(LED_RED, HIGH);

                //PORTB |= (1<< LED_GREEN);
                //PORTB |= (1<< LED_RED);

                GPIO_write_high(&PORTB, LED_GREEN);
                GPIO_write_low(&PORTB, LED_RED);
            }
            else {
                led_value = 0;
                // Clear pin(s) to LOW
                //digitalWrite(LED_GREEN, LOW);
                //digitalWrite(LED_RED, LOW);

                //PORTB &= ~(1<< LED_GREEN);
                //PORTB &= ~(1<< LED_RED);

                GPIO_write_low(&PORTB, LED_GREEN);
                GPIO_write_high(&PORTB, LED_RED);
            }
        }
        else
        {
            GPIO_write_low(&PORTB, LED_GREEN);
            GPIO_write_low(&PORTB, LED_RED);
        }
    }

    // Will never reach this
    return 0;
}