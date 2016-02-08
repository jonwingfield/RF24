/*
    5-10-07
    Copyright Spark Fun Electronics© 2007
    Nathan Seidle
    nathan at sparkfun.com
    
    ATmega168
	
	Example Blink
	Toggles all IO pins at 1Hz
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include "RF24_c.h"
#include "nRF24L01.h"

#undef BAUD
#define BAUD 9600

//Define functions
//======================
void ioinit(void);      //Initializes IO
void delay_ms(uint16_t x); //General purpose delay
static int uart_putchar(char c, FILE *stream);
uint8_t uart_getchar(void);
//======================
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

const uint8_t pipes[][6] = {"1Node","2Node"};

// PORTB
RF24 rf24;

int main (void)
{
    RF24* radio = &rf24;
    ioinit(); //Setup IO pins and defaults

    for(int i=0; i<100; i++) {
      printf("Hello 2\n");
      delay_ms(300);
    }

    rf24_init_stack(&rf24, 6,7);

    printf("Final hello!\n");

    rf24_begin(radio);
    rf24_setDataRate(radio, RF24_250KBPS);

    /* rf24_setChannel(radio, 4); */

    printf("Channel set!\n");

    delay_ms(100);

    printf("Channel: %d\n", rf24_getChannel(radio));

    rf24_openWritingPipe(radio, pipes[0]);
    rf24_openReadingPipe(radio, 1, pipes[1]);

    unsigned long time = 22;
    while (1) {
      			// First, stop listening so we can talk.
			rf24_stopListening(radio);

			// Take the time, and send it.  This will block until complete

			printf("Now sending...\n");

			bool ok = rf24_write(radio, &time, sizeof(unsigned long) );

			if (!ok){
				printf("failed.\n");
			} else {
				printf("sent.\n");
			}
			// Now, continue listening
			rf24_startListening(radio);

      uint16_t ticks = 0;
			bool timeout = false;
			while ( ! rf24_available(radio) && ++ticks < 250) {
        _delay_ms(1);
			}


			// Describe the results
			if ( ticks >= 250)
			{
				printf("Failed, response timed out.\n");
			}
			else
			{
				// Grab the response, compare, and send to debugging spew

				rf24_read(radio, &time, sizeof(time) );

				// Spew it
				printf("Got response %d\n",time);
			}

			_delay_ms(1000);
    }

    return(0);
}

void ioinit (void)
{
    //1 = output, 0 = input
    /* DDRB = 0b11111111; //All output */
    /* DDRC = 0b00000000; //All input */
    /* DDRD = 0; //PORTD (RX on PD0) */
    
#include <util/setbaud.h>
    //USART Baud rate
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    // enable receive/transmit
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    stdout = &mystdout; //Required for printf init
}

static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);
  
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    
    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSR0A & (1<<RXC0)) && UDR0 <= 10) asm volatile("nop");
    return(UDR0);
}

//General short delays
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}
