/***********************************************************************
 * 
 * Blink two LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_ONBOARD PB5  // Arduino Uno on-board LED
#define LED_RED PB0    // External active-low LED
#define LED_GREEN PB1 // External active-low LED


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs using the internal 8- and 16-bit 
 *           Timer/Counter.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Set pins where LEDs are connected as output
    GPIO_mode_output(&DDRB, LED_ONBOARD);
    GPIO_mode_output(&DDRB, LED_RED);
    GPIO_mode_output(&DDRB, LED_GREEN);

    // Configuration of 16-bit Timer/Counter1 for LED blinking
    // Set the overflow prescaler to 262 ms and enable interrupt
    TIM1_OVF_1SEC
    TIM1_OVF_ENABLE

    TIM0_OVF_4MS
    TIM0_OVF_ENABLE

    TIM2_OVF_512US
    TIM2_OVF_ENABLE

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Toggle on-board LED.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    GPIO_write_toggle(&PORTB, LED_ONBOARD);
}
ISR(TIMER0_OVF_vect)
{
  static uint8_t no_of_overflows = 0;
  
  no_of_overflows++;
  if (no_of_overflows >= 100)
  {
      GPIO_write_toggle(&PORTB, LED_RED);
  }

}
ISR(TIMER2_OVF_vect)
{
  static uint8_t no_of_overflows = 0;

  no_of_overflows++;
  if (no_of_overflows >= 200)
  {
    GPIO_write_toggle(&PORTB, LED_GREEN);
  }
}
