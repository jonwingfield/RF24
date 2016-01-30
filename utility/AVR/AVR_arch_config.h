/*
 TMRh20 2015
 Generic AVR (via avr-gcc/libc) configuration fiole
*/

#ifndef __RF24_ARCH_CONFIG_H__
#define __RF24_ARCH_CONFIG_H__

  /*** USER DEFINES:  ***/  
  //#define FAILURE_HANDLING
  //#define MINIMAL
  /**********************/

  #define rf24_max(a,b) (a>b?a:b)
  #define rf24_min(a,b) (a<b?a:b)


  #include <time.h>
  #include <string.h>
  #include <avr/io.h>
  #include <stddef.h>  
  #include <util/delay.h>
  
  /**** TYPES ********/

  #define byte    uint8_t

  /**** END TYPES ***/

  /**** AVR FUNCTIONS **/

  #define delayMicroseconds _delay_loop_1
  #define delay             _delay_loop_2

  /**** ARDUINO defines **/

  #define LOW    0x0
  #define HIGH   0x1
  // TODO: check this
  #define OUTPUT 0x1

  #define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
  #define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

  #define ARDUINO_PORT             PORTB
  #define ARDUINO_DDR              DDRB

  #define digitalWrite(pin, val)   ((val) ? (sbi(PORTB, (pin))) : (cbi(PORTB, (pin))))
  #define pinMode(pin,dir)         ((dir) ? (sbi(DDRB, (pin))) : (cbi(DDRB, (pin))))

  #define MSBFIRST 0
  #define LSBFIRST 1

  #define SCK      PB5
  #define SS       PB2
  #define MISO     PD4
  #define MOSI     PD3

  // Include the header file for SPI functions ( Main SPI code is contained in RF24.cpp for simplicity )
  #include "spi.h"

  #define _SPI SPI
  
  #ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
  #else
	#define IF_SERIAL_DEBUG(x)
	#if defined(RF24_TINY)
	#define printf_P(...)
    #endif
  #endif

  #include <avr/pgmspace.h>
  #define PRIPSTR "%S"
  
  // TODO: fix this
  #define millis()   0

#endif // __RF24_ARCH_CONFIG_H__

